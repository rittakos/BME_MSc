#ifndef DBS_H
#define DBS_H


#include "geometry.hh"
#include "object.hh"


class DBS : public Object
{
public:
    DBS(std::string filename);

    virtual void draw(const Visualization &vis) const override;
    virtual void drawWithNames(const Visualization &vis) const override;
    virtual Vector postSelection(int selected) override;
    virtual void movement(int selected, const Vector &pos) override;
    virtual void updateBaseMesh() override;
    virtual bool reload() override;

    virtual Vector normal(BaseMesh::VertexHandle vh) const override;
    virtual double meanCurvature(BaseMesh::VertexHandle vh) const override;

    virtual ~DBS();

    static double fullness;

private:
    size_t degree[2];
    size_t num[2];
    std::vector<double> knots_u;
    std::vector<double> knots_v;
    std::vector<Vector> control_points;
    std::vector<std::vector<Vector>> control_points_matrix;

    float maxU = 0;
    float minU;
    float maxV = 0;
    float minV;


private:
    void calcControlPoints();

    std::map<size_t, bool> innerPoint;

    static std::vector<Geometry::Point3D> toPoint3DVec (const std::vector<Vector>& in);
    static std::vector<Vector> toVec3DVec (const std::vector<Geometry::Point3D>& in);
    static Geometry::Point3D toPoint3D (const Vector& in);
    static Vector toVec3D (const Geometry::Point3D& in);
};

#endif // DBS_H
