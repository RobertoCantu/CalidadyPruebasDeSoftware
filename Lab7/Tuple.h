//Autor: Roberto Cantu Reyes A01196704
//Fecha de creacion 14/09/2021
//Fecha de modificacion 05/11/2021
//Este es el archivo que se encarga de guardar los valores en una tupla
//.b=21
class Tuple {
    private:
        double w;
        double x;
        double y;
        double z;

    public:
    Tuple();
    double getW();
    double getX();
    double getY();
    double getZ();
    void setW(double);
    void setX(double);
    void setY(double);
    void setZ(double);

};

//Constructor 
Tuple::Tuple(){
    w = 0;
    x = 0;
    y = 0;
    z = 0;
}

//Getters and Setters
double Tuple::getW(){
    return w;
}

double Tuple::getX(){
    return x;
}

double Tuple::getY(){
    return y;
}

double Tuple::getZ(){
    return z;
}

void Tuple::setW(double w){
    this->w = w;
}

void Tuple::setX(double x){
    this->x = x;
}

void Tuple::setY(double y){
    this->y = y;
}

void Tuple::setZ(double z){
    this->z = z;
}