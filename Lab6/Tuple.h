//Autor: Roberto Cantu Reyes A01196704
//Fecha de creacion 14/09/2021
//Fecha de modificacion 15/09/2021
//Este es el archivo que se encarga de guardar los valores en una tupla
//.b=21
class Tuple {
    private:
        double x;
        double y;

    public:
    Tuple();
    double getX();
    double getY();
    void setX(double);
    void setY(double);

};

//Constructor 
Tuple::Tuple(){
    x = 0;
    y = 0;
}

double Tuple::getX(){
    return x;
}

double Tuple::getY(){
    return y;
}

void Tuple::setX(double x){
    this->x = x;
}

void Tuple::setY(double y){
    this->y = y;
}