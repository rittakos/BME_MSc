#version 300 es 
precision highp float;
precision highp sampler3D;


uniform struct {
  vec3 position;
  mat4 rayDirMatrix;
} camera;

uniform struct {
  vec4 position;
  vec4 powerDensity;
} lights[2];

uniform struct{
  samplerCube env;
  sampler3D volume;
  vec3 mode;
} scene;

in vec2 tex;
in vec4 rayDir;

out vec4 fragmentColor;

struct Hit 
{ 
  float In; 
  float Out; 
};

struct Ray 
{ 
  vec3 start; 
  vec3 inverse; 
};

const float surfaceDensity  = 0.1;
const float epsilon         = 0.01;


bool inBox(const Ray r, out Hit hit) 
{
    vec3 bot = r.inverse * (vec3(0.0, 0.0, 0.0) - r.start);
    vec3 top = r.inverse * (vec3(1.0, 1.0, 1.0) - r.start);
    vec3 tmin = min(top, bot);
    vec3 tmax = max(top, bot);
    vec2 t = max(tmin.xx, tmin.yz);
    float t0 = max(t.x, t.y);
    t = min(tmax.xx, tmax.yz);
    float t1 = min(t.x, t.y);
    
    hit.In = t0;
    hit.Out = t1;

    return t1 > max(t0, 0.0);
}

float density(vec3 pos) 
{
    const float min = 0.0;
    const float max = 1.0;
    if ((pos.x < min || pos.x > max) || 
        (pos.y < min || pos.y > max) || 
        (pos.z < min || pos.z > max)) 
    {
        return 0.0;
    }
    return texture(scene.volume, vec3(1, 1, 1) - pos).x;
}

vec3 getNormal(vec3 pos) 
{
    float dx, dy, dz;
    dx = density(pos + vec3(epsilon, 0, 0)) - density(pos + vec3(-epsilon, 0, 0));
    dy = density(pos + vec3(0, epsilon, 0)) - density(pos + vec3(0, -epsilon, 0));
    dz = density(pos + vec3(0, 0, epsilon)) - density(pos + vec3(0, 0, -epsilon));
    return normalize(vec3(dx, dy, dz));
}

vec4 diffuse(vec3 pos)
{
    vec3 normal = getNormal(pos);
    vec3 lightDir = normalize (lights[1].position.xyz - pos);
    float d = length(lights[1].position.xyz - pos);

    float lambert = max(dot(lightDir, normal), 0.0);
    float specular = 0.0;

    if (lambert > 0.0) 
    {
        vec3 viewDir = normalize(camera.position - pos);
        vec3 halfDir = normalize(lightDir + viewDir);

        float specAngle = max(dot(halfDir, normal), 0.0);
        specular = pow(specAngle, 10.0);
    }
    vec3 color =  vec3(0.1, 0.1, 0.1) +
                  vec3(0.7, 0.2, 0.2) * lambert * lights[1].powerDensity.xyz / (d * d) +
                  vec3(0.5, 0.5, 0.5) * specular * lights[1].powerDensity.xyz / (d * d);
    return vec4(color, 1.0);
}

vec3 between(vec3 prev, vec3 next, float dens) 
{
    vec3 p = next;
    for (int idx = 0; idx < 32; ++idx) 
    {
        p = (prev + next) / 2.0;
        if ((density(p) > dens) == (density(p) > dens))
          prev = p;
        else
          next = p;
    }

    return p;
}

vec3 getSurface(float d)
{
    vec3 normRayDir = normalize(rayDir.xyz);
    Hit hit;
    Ray ray = Ray(camera.position, vec3(1./normRayDir.x, 1./normRayDir.y, 1./normRayDir.z));
    if (!inBox(ray, hit)){
        return vec3(-2, -2, -2);
    }

    vec3 pos = camera.position + normRayDir * hit.In;
    const int stepCount = 150;
    vec3 step = normRayDir * (hit.Out - hit.In) / float(stepCount);
    float lastDensity = 0.0;

    for (int idx = 0; idx < stepCount; ++idx) 
    {
      if(lastDensity >= d)
        return between(pos, pos - step, d);
      pos += step;
      lastDensity = density(pos);
    }

    return vec3(-1.0, -1.0, -1.0);
}



float shadow(vec3 pos) 
{
    vec3 lightDir = normalize(-lights[1].position.xyz - pos);
    pos = pos + lightDir * 0.1;

    Hit hit;
    Ray ray = Ray(pos, vec3(1./lightDir.x, 1./lightDir.y, 1./lightDir.z));
    inBox(ray, hit);

    const int steps = 150;
    vec3 step = lightDir * 0.01 / float(steps);
    float lastDensity = 0.0;

    for (int idx = 0; idx < steps; ++idx) 
    {
      pos += step;
      lastDensity = density(pos);
      if (lastDensity >= surfaceDensity)
        return surfaceDensity / lastDensity;
    }

    return 1.0;
}

void main(void) {
  vec3 surface;

  if(scene.mode.x == 0.0) //diffuse
  {
    surface = getSurface(surfaceDensity);

    if (surface.x > 0.0) 
        fragmentColor = diffuse(surface);
        
  } else if (scene.mode.x == 1.0) //onion
  {
    const float surfaces[4] = float[](0.8, 0.6, 0.4, 0.2);
    const vec4 colors[4] = vec4[](vec4(1, 1, 1, 0.6), vec4(1, 0, 0, 0.3), vec4(0, 1, 0, 0.4), vec4(0, 0, 1, 0.5));
    vec3 color;

    for (int idx = 0; idx < 4; ++idx) 
    {
        surface = getSurface(surfaces[idx]);
        if (surface.x == -2.0) 
          break;
        if (surface.x > 0.0) 
        {
            color += colors[idx].xyz * colors[idx].w * (1.0 - dot(normalize(rayDir).xyz, getNormal(surface)));
        }
    }

    fragmentColor = vec4(color, 1);
  }else if (scene.mode.x == 2.0) //shadow
  {
    surface = getSurface(surfaceDensity);
    if (surface.x > 0.0)
    {
      fragmentColor = texture(scene.volume, vec3(1, 1, 1) - surface) * 2.0;
      fragmentColor.xyz = fragmentColor.xyz * shadow(surface);
    }
  }

  if (surface.x > -2.0) // show Box
  {
    fragmentColor = vec4(fragmentColor.xyz * (0.8) + 0.2, 1.0);
  }
}