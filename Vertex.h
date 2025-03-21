
#ifndef VERTEX_H
#define VERTEX_H



class Vertex {
public:
    Vertex(double x, double y, double z);
    double getX() const {return x;}
    double getY() const {return y;}
    double getZ() const {return z;}
    void setX(double x) {this->x = x;}
    void setY(double y) {this->y = y;}
    void setZ(double z) {this->z = z;}

private:
    double x;
    double y;
    double z;
};



#endif //VERTEX_H
