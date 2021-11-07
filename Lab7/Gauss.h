//Autor: Roberto Cantu Reyes A01196704
//Fecha de creacion 05/11/2021
//Fecha de modificacion 05/11/2021
//Este es el archivo que resuelve el sistema de ecuaciones
//mediante el metodo de eliminacion de Gauss
#include <vector>
using namespace std;
class Gauss {
    private:
    vector <double> result;


    public:
    Gauss();
    vector<double> getResult();
    void gaussElimination(int m,int n,double [4][5]);

};

//Constructor 
Gauss::Gauss(){
    result = {0,0,0,0};

}

//Getter
vector<double> Gauss::getResult(){
    return result;
}

//Este metodo recibe las filas, columnas y una matriz como parametro
//Se encarga de resolver el sistema de ecucaciones mediante el metodo
//de eliminacion de Gauss y guarda el resultado en el atributo result
//No tiene valor de retorno
//.i
void Gauss::gaussElimination(int m,int n,double a[4][5]){
 int i,j,k;
    for(i=0;i<m-1;i++){
        //Pivoteo parcial
        for(k=i+1;k<m;k++){
            if( a[i][i] < a[k][i]){
                //Hacer un swap de filas
                for(j=0;j<n;j++){                
                    double temp;
                    temp=a[i][j];
                    a[i][j]=a[k][j];
                    a[k][j]=temp;
                }
            }
        }
        //Eliminacion de Gauss
        for(k=i+1;k<m;k++){
            double  ratio=a[k][i]/ a[i][i];
            for(j=0;j<n;j++){
                a[k][j]=a[k][j]-ratio*a[i][j];
            }
        } 
    }
    //Back-substitution
    for(i=m-1;i>=0;i--){
        result[i]=a[i][n-1];
        for(j=i+1;j<n-1;j++){
            result[i]=result[i]-a[i][j]*result[j];
        }
        result[i]=result[i]/a[i][i];
    }
}