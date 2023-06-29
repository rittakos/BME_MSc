#version 300 es
precision highp float;
precision highp sampler3D;

in vec3 rayDir;
out vec4 fragmentColor;

uniform struct {
    mat4 rayDirMatrix;
    vec3 position;
} camera;

uniform struct {
    sampler3D volume;
    vec3 lightPos;
    vec3 mode;
} scene;

struct Hit { float tmin; float tmax; };
struct Ray { vec3 origin; vec3 dir; vec3 invDir; };

const float surfaceDensity = 23./255.;

bool BoxIntersect(const vec3 boxMin, const vec3 boxMax, const Ray r, out Hit hit) {
    vec3 tbot = r.invDir * (boxMin - r.origin);
    vec3 ttop = r.invDir * (boxMax - r.origin);
    vec3 tmin = min(ttop, tbot);
    vec3 tmax = max(ttop, tbot);
    vec2 t = max(tmin.xx, tmin.yz);
    float t0 = max(t.x, t.y);
    t = min(tmax.xx, tmax.yz);
    float t1 = min(t.x, t.y);
    hit.tmin = t0;
    hit.tmax = t1;
    return t1 > max(t0, 0.0);
}

float density(vec3 p) {
    const float lower = 0.;
    const float upper = 1.;
    if ((p.x<lower || p.x>upper) || (p.y<lower || p.y>upper) || (p.z<lower || p.z>upper)) {
        return 0.;
    }
    return texture(scene.volume, vec3(1, 1, 1)-p).r;
}

vec3 normal(vec3 p) {
    const float eps = 0.01;
    float dx, dy, dz;
    dx = density(p + vec3(eps, 0, 0)) - density(p + vec3(-eps, 0, 0));
    dy = density(p + vec3(0, eps, 0)) - density(p + vec3(0, -eps, 0));
    dz = density(p + vec3(0, 0, eps)) - density(p + vec3(0, 0, -eps));
    return normalize(vec3(dx, dy, dz));
}

int side(vec3 p, float dens) {
    return density(p) > dens ? -1 : 1;
}

vec3 BlinnPhong(vec3 pos){
    const vec3 lightColor = vec3(1.0, 1.0, 1.0);
    const float lightPower = 40.0;
    const vec3 ambientColor = vec3(30./255., 215./255., 96./255.)/5.;
    const vec3 diffuseColor = vec3(30./255., 215./255., 96./255.);
    const vec3 specColor = vec3(0.5, 0.5, 0.5);
    const float shininess = 12.0;

    vec3 normal = normal(pos);
    vec3 lightDir = scene.lightPos - pos;
    float distance = length(lightDir);
    distance = distance * distance;
    lightDir = normalize(lightDir);

    float lambertian = max(dot(lightDir, normal), 0.0);
    float specular = 0.0;

    if (lambertian > 0.0) {
        vec3 viewDir = normalize(camera.position-pos);
        vec3 halfDir = normalize(lightDir + viewDir);
        float specAngle = max(dot(halfDir, normal), 0.0);
        specular = pow(specAngle, shininess);
    }
    vec3 colorLinear = ambientColor +
    diffuseColor * lambertian * lightColor * lightPower / distance +
    specColor * specular * lightColor * lightPower / distance;
    return colorLinear;
}

vec3 bisect(vec3 pos, vec3 pos2, float dens) {
    vec3 inbetween;
    for (int i = 0; i < 16; i++) {
        inbetween = (pos + pos2)/2.;
        if (side(pos, dens) == side(inbetween, dens))
        pos = inbetween;
        else
        pos2 = inbetween;
    }
    return inbetween;
}

vec3 findSurface(float dens){
    vec3 rayDirNorm = normalize(rayDir);
    Hit hit;
    Ray ray = Ray(camera.position, rayDirNorm, vec3(1./rayDirNorm.x, 1./rayDirNorm.y, 1./rayDirNorm.z));
    if (!BoxIntersect(vec3(0, 0, 0), vec3(1, 1, 1), ray, hit)){
        return vec3(-2, 0, 0);
    }

    vec3 pos = camera.position + rayDirNorm * hit.tmin;
    const int steps = 128;
    vec3 step = rayDirNorm * (hit.tmax - hit.tmin) / float(steps);
    float lastDensity = 0.;

    for (int i = 0; i < steps && lastDensity < dens; i++) {
        pos += step;
        lastDensity = density(pos);
    }

    if (lastDensity >= dens) {
        return bisect(pos, pos - step, dens);
    }

    return vec3(-1, 0, 0);
}

vec4 boxTint(vec4 color) {
    const float boxHue = 1.;
    const vec3 boxColor = vec3(boxHue, boxHue, boxHue);
    const float boxStrength = 0.15;
    return vec4(color.xyz*(1.-boxStrength) + boxColor*boxStrength, 1.);
}

bool shadowed(vec3 pos) {
    vec3 lightDir = normalize(scene.lightPos*-1. - pos);
    pos = pos+lightDir*0.1;

    Hit hit;
    Ray ray = Ray(pos, lightDir, vec3(1./lightDir.x, 1./lightDir.y, 1./lightDir.z));
    BoxIntersect(vec3(0, 0, 0), vec3(1, 1, 1), ray, hit);

    const int steps = 128;
    vec3 step = lightDir * 0.01 / float(steps);
    float lastDensity = 0.;

    for (int i = 0; i < steps && lastDensity < surfaceDensity; i++) {
        pos += step;
        lastDensity = density(pos);
    }

    return lastDensity >= surfaceDensity;
}

void main(void) {
    vec3 rayDirNorm = normalize(rayDir);
    fragmentColor = vec4(rayDirNorm, 1.);
    vec3 surface;
    float mode = mod(scene.mode.x, 3.);

    // Blinn-Phong
    if (mode == 0.) {
        surface = findSurface(surfaceDensity);
        if (surface.x > 0.) {
            fragmentColor = vec4(BlinnPhong(surface), 1);
        }
    }

    // layered
    if (mode == 1.) {
        const float surfaces[3] = float[](0.6, 0.4, 0.15);
        const vec4 colors[3] = vec4[](vec4(1, 0, 0, 0.3), vec4(1, 1, 0, 0.4), vec4(0, 1, 0, 0.3));
        vec3 color;
        for (int i = 0; i < 3; i++) {
            surface = findSurface(surfaces[i]);
            if (surface.x == -2.) break;
            if (surface.x > 0.) {
                color += colors[i].xyz * colors[i].w *
                (1.-dot(rayDirNorm, normal(surface)));
            }
        }
        fragmentColor = vec4(color, 1);
    }

    // self shadow
    if (mode == 2.) {
        surface = findSurface(surfaceDensity);
        if (surface.x > 0.) {
            fragmentColor = vec4(vec3(1, 1, 1)-normal(surface), 1);
            if (shadowed(surface)) {
                fragmentColor.xyz = fragmentColor.xyz*0.2;
            }
        }
    }

    if (mod(scene.mode.y, 2.) == 0. && surface.x > -2.) {
        fragmentColor = boxTint(fragmentColor);
    }
}
