#include <iostream>
#include <string.h>
#include <windows.h>
#include <fstream>
#include <sstream>
#define DELTA 5
char Sexo[2][10]={"Masculino","Femenino"};
using namespace std;
void gotoxy(int x,int y){ //columnasxrenglones
     HANDLE hcon;
     hcon = GetStdHandle(STD_OUTPUT_HANDLE);
     COORD dwPos;
     dwPos.X = x;
     dwPos.Y= y;
     SetConsoleCursorPosition(hcon,dwPos);
}
class tiempo{
  protected:
    int dia;
    int mes;
    int anho;
  public:
    int getDia(){
        return dia;
    }
    int getMes(){
        return mes;
    }
    int getAnho(){
        return anho;
    }
    tiempo(){
        dia=1;
        mes=1;
        anho=1999;
    }
    void terminarDia(){

        if(dia==31){
            if(mes==12){
                anho++;
            }
            else mes++;
        }
        else dia++;
    }
    void llenar(){
        cout<<"\tRegistro de Fecha:"<<endl;
        do{
        cout<<"Ingrese el d"<<char(161)<<"a: ";cin>>dia;
        }while(dia>31 || dia<0);
        do{
        cout<<"El mes: ";cin>>mes;
        }while(mes<0 || mes>12);
        do{
        cout<<"Por ultimo el a"<<char(164)<<"o: ";cin>>anho;
        }while(anho<1900 || anho>2030);
        cout<<"Fecha ingresada con exito..."<<endl;
    }
    void mostrar(){
        gotoxy(80,1);
        cout<<"Fecha Actual: "<<dia<<"/"<<mes<<"/"<<anho<<endl;
    }

};
class fechaC : public tiempo{
  protected:
    bool estado;//true disponible, false no disponible
  public:
   fechaC(){
        dia=1;
        mes=1;
        anho=1999;
        estado=true;
    }
   bool getEstado(){
       return estado;
   }
   void descativarMovimientos(){
       estado=false;
   }
   void llenar(tiempo fecha){
           cout<<"\tRegistro de Fecha:"<<endl;
           do{
           cout<<"Ingrese el d"<<char(161)<<"a: ";cin>>dia;
           }while(dia>31 || dia<0);
           do{
           cout<<"El mes: ";cin>>mes;
           }while(mes<0 || mes>12);
           do{
           cout<<"Por ultimo el a"<<char(164)<<"o: ";cin>>anho;
           }while((fecha.getAnho()-anho)<18);
           cout<<"Fecha ingresada con exito..."<<endl;
       }
   void set(int dia,int mes,int anho){
       this->dia=dia;
       this->mes=mes;
       this->anho=anho;
      }

    void activarMovimientos(){
        estado=true;
    }
   void mostrar(){
       cout<<dia<<"/"<<mes<<"/"<<anho<<endl;
   }
};
char TMon [3][15]={" ","Soles","Dolares"};
char TEst [4][15]={" ","Habilitada ","Bloqueada","Cancelada"};
char Operacion[3][9]={" ","Retiro","Deposito"};
class Baucher{
private:
    int operacion;
    fechaC fecha;
    float monto,disponible;
    char Ncuenta[15];
public:
    Baucher(){
        operacion=0;
        monto=0.0;
        disponible=0.0;
        Ncuenta[0]='\x0';
    }
    void set(int operacion, tiempo fecha, float monto, float disponible, char Ncuenta[]){
        this->disponible=disponible;
        this->monto=monto;
        this->operacion=operacion;
        strcpy(this->Ncuenta,Ncuenta);
        this->fecha.set(fecha.getDia(),fecha.getMes(),fecha.getAnho());
        stringstream registro;
            registro <<"D:\\"<<operacion<<monto<<disponible<<Ncuenta<<".txt";
            string resultado = registro.str( );
        ofstream archivo_salida(resultado.c_str());
        archivo_salida <<"\tMi fortuna\n"<<"Fecha: "<<fecha.getDia()<<"/"<<fecha.getMes()<<"/"<<fecha.getAnho()<<endl
                      <<"\t\t\t"<<Operacion[operacion]<<endl<<"Numero de cuenta: "<<Ncuenta<<"\nSaldo Disponible: "<<disponible<<endl;
        archivo_salida.close();
    }
    void mostrar(){
        cout<<"\t\t\tMiFortuna"<<endl
            <<"\tFecha";fecha.mostrar();
        cout<<"\t\t\t"<<Operacion[operacion]<<endl
            <<"Monto: "<<monto<<endl
            <<"Numero de cuenta: "<<Ncuenta<<endl
            <<"Saldo Disponible: "<<disponible<<endl;
    }
};
class ListaBaucher{
private:
    Baucher *data;
    int total;
    int max;
public:
    ListaBaucher(){
        data = NULL;
        total=0;
        max=0;
    }
    ~ListaBaucher(){
        delete data;
        total=0;
        max=0;
    }
    void crece(){
        Baucher *aux= new Baucher[total+DELTA];
        for (int i = 0; i < total; ++i) {
           aux[i]=data[i];
        }
        data=aux;
        max+=DELTA;
    }
    void inserta(int operacion, tiempo fecha, float monto, float disponible, char Ncuenta[]){
        if(total==max)crece();
        data[total].set(operacion, fecha, monto, disponible,  Ncuenta);
        total++;
    }
    void Listar(){
        cout<<"Movimientos"<<endl
            <<"****************************************"<<endl;
        for (int i = 0; i < total; ++i) {
            data[i].mostrar();
        cout<<"****************************************"<<endl;
        }
    }
};

class Cuenta{
    protected:
        char NumCuenta[15];
        char Cliente [30];
        float Monto;
        int Moneda;
        int Estado;
        ListaBaucher Movimientos;
        fechaC fecha;
    public:
        int getEstado(){
            return Estado;
        }
        char* getNumCuenta(){
            return NumCuenta;
        }
        int getMoneda(){
            return Moneda;
        }
        fechaC getFecha(){
            return fecha;
        }
        int getMonto(){
            return Monto;
        }
       virtual void Deposito(tiempo fecha){
            float Dep ;
            cout <<"Ingrese Monto a depositar: ";
            cin >> Dep ;
            Monto = Monto + Dep;
            Movimientos.inserta(2,fecha,Dep,Monto,NumCuenta);
       }
       virtual void Retiro(tiempo fecha){
           float Ret ;
           cout <<"Ingrese Monto a Retirar: ";
           cin >> Ret ;
           if(Ret<Monto){
           Monto = Monto - Ret;
           Movimientos.inserta(1,fecha,Ret,Monto,NumCuenta);
           }
           else{
               cout << "Usted no tiene saldo suficiente en su cuenta para realizar este retiro."<< endl;
           }
       }
        void setMonto (int Monto){
            this->Monto=Monto;
        }
         void validarEstado(tiempo fecha){
            if(this->fecha.getEstado()==true){
               if(Estado==1)mostraOperaciones(fecha);
               else cout<<"La cuenta no esta habilitada"<<endl;
            }
            else cout<<"No puede realizar mas operaciones por este mes.."<<endl;
        }
        virtual void Activar(){
            fecha.activarMovimientos();
        }
        Cuenta();
        virtual ~Cuenta(){
            //se aplica para que no salga la advertencia de no poseer un destructor virtual, pero es inutil tener uno en esta clase ya que no se usa memoria dinamica.
        }
        virtual void ListaEstado(){
            cout<<"Numero de cuenta: "<<NumCuenta<<"\tMonto Actual: "<<Monto<<"\tEstado actual: "<<TEst[Estado]<<endl;
        }
         void mostraOperaciones(tiempo fecha){
            system("cls");
            fecha.mostrar();
            int op;
            this->Presentar();
            cout<<"Operaciones a realizar: "<<endl
                <<"1)Deposito"<<endl
                <<"2)Retiro"<<endl
                <<"3)Bloquear o Cerrar cuenta"<<endl
                <<"4)Mostrar los movimientos"<<endl;
            do{
                cout<<"Ingrese una opcion a realizar";cin>>op;
            }while(op>4 || op<1);
            switch (op) {
            case 1:
                Deposito(fecha);
                break;
            case 2:
                Retiro(fecha);
                break;
            case 3:
                cambiarEstado();
                break;
            case 4:
                MostrarOperaciones();
                break;
            }
        }
        void cambiarEstado(){
            int op;
            cout<<"Operaciones a realizar: "<<endl
                <<"1)Cancelar la cuenta"<<endl
                <<"2)Bloquear la cuenta"<<endl
                <<"3)Dejarla Habilitada"<<endl;
            do{
                cout<<"Ingrese una opcion a realizar";cin>>op;
            }while(op>3 || op<1);
            switch (op) {
            case 1:
                Estado=3;
                break;
            case 2:
                Estado=2;
                break;
            case 3:
                break;
         }
        }
        void MostrarOperaciones(){
            Movimientos.Listar();
        }
        void Leer(char cod[], tiempo fechaActual, char nombre[]);
        virtual void Presentar();


};
Cuenta ::Cuenta(){
    NumCuenta[0]= '\x0';
    Cliente[0]='\x0';
    Monto=0.0;
    Estado=0;
    Moneda=0;
}
void Cuenta::Leer(char cod[], tiempo fechaActual, char nombre[]){
    strcpy(NumCuenta,cod);
    strcpy(Cliente,nombre);
    fecha.set(fechaActual.getDia(),fechaActual.getMes(),fechaActual.getAnho());
    cout << "[1]Soles "<<endl ;
    cout << "[2]Dolares "<< endl;
    cout << "Ingrese tipo de moneda: ";
    cin >> Moneda;
    cout << "Ingrese monto de apertura: ";
    cin >> Monto;

    cout << "[1]Habilitada"<<endl;
    cout << "[2]Bloqueada"<<endl;
    cout << "[3]Cancelada"<<endl;
    do{
    cout << "Ingrese estado de la cuenta: ";
    cin >> Estado;
    }while(Estado<1 || Estado>3);
}
void Cuenta::Presentar(){
    cout << "Numero de Cuenta: "<<NumCuenta << endl;
    cout << "nombre del Titular de la cuenta: "<<Cliente << endl;
    cout << "Tipo de moneda: "<< TMon[Moneda] << endl;
    cout << "Monto:" << Monto << endl;
    cout << "Fecha de Apertura ";fecha.mostrar();
    cout << "Estado de la cuenta: " << TEst[Estado]<<endl;
}


class Ahorro : public Cuenta {
    protected:
        int Oper;
        float Interes;
    public:
        Ahorro();
        void Leer(char cod[], tiempo fechaActual, char nombre[]);
        void Presentar();
        void Deposito(tiempo fecha);
        void Retiro(tiempo fecha);
        void Activar(){
            Cuenta::Activar();
            Oper=0;
        }
};
Ahorro ::Ahorro() : Cuenta(){
    Oper=0;
    Interes=0;
}
void Ahorro::Leer(char cod[], tiempo fechaActual, char nombre[]){
    Cuenta::Leer(cod,fechaActual,nombre);
    cout << "Ingrese el interes que cobrara el banco al cliente por su cuenta: ";
    cin >> Interes;
}
void Ahorro::Presentar(){
    Cuenta::Presentar();
    cout << "Interes:" << Interes << endl;
}
void Ahorro ::Deposito(tiempo fecha){
    Cuenta::Deposito(fecha);
    Oper++;
    cout<<"Suma una mas"<<endl;
    system("pause");
    if(Oper==5) this->fecha.descativarMovimientos();
}
void Ahorro ::Retiro(tiempo fecha){
    Cuenta::Retiro(fecha);
    Oper++;
    if(Oper==5) this->fecha.descativarMovimientos();
}
class Fijo : public Cuenta{
    protected:
        float dineroInicial;
        float Interes;
        int Tiempo;
        float MontoFinal;
    public:
        Fijo();
        void Leer(char cod[], tiempo fechaActual, char nombre[]);
        void Presentar();
        void Retiro(){
            cout<<"Si retira ahora se le penalizara con la devolucion de su Dinero Inicial y se bloqueara la tarjeta"<<endl
                <<"Devido a que no cumplio con el pacto"<<endl;
            char rpta[2];
            do{
                cout<<"¿Desea continuar?[SI-NO]: ";cin>>rpta;
            }while(strcmp(rpta,"SI")!=0 && strcmp(rpta,"NO")!=0);
            if(strcmp(rpta,"SI")==0){
                cout<<"Retiro de "<<dineroInicial<<" Realizado"<<endl;
                Estado=2;
            }
        }
        void ListaEstado(){
            cout<<"Monto final: "<<MontoFinal;
            Cuenta::ListaEstado();
        }
};
Fijo::Fijo():Cuenta(){
    Tiempo=0;
    Interes=0;
    MontoFinal=0.0;
}
void Fijo::Leer(char cod[], tiempo fechaActual, char nombre[]){
       Cuenta :: Leer(cod,fechaActual,nombre);
       cout << "Ingrese el tiempo en meses de su cuenta a plazo fijo: ";
       cin >> Tiempo;
       dineroInicial=Monto;
       cout << "Ingrese el interes que pagar el banco al cliente por su cuenta: ";
       cin >> Interes;
       MontoFinal=Monto;
       for (int i = 0; i < Tiempo; ++i) {
           MontoFinal+=Monto*Interes;
       }
}
void Fijo::Presentar(){
    Cuenta::Presentar();
    cout << "Tiempo de la cuenta: " << Tiempo << endl;
    cout << "Interes:" << Interes << endl;
}

class ListaCuentas{
protected:
    Cuenta *data;
    int total;
    int max;
public:
    ListaCuentas(){
        data = NULL;
        total=0;
        max=0;

    }
    ~ListaCuentas(){
        delete data;
        total=0;
        max=0;
    }
    void crece(){
        Cuenta *aux= new Cuenta[total+DELTA];
        for (int i = 0; i < total; ++i) {
           aux[i]=data[i];
        }
        data=aux;
        max+=DELTA;
    }
    void inserta(char cod[], tiempo fecha, char nombre[]){
        int tipo;
        cout<<"Ingrese el tipo de Cuenta que desea registrar: "<<endl
            <<"1)Ahorro"<<endl
            <<"2)Plazo fijo"<<endl;
        do{
            cout<<"[1-2]: ";cin>>tipo;
        }while(tipo>2 || tipo<1);
        if(tipo==1) {
            Ahorro aux;
            aux.Leer(cod,fecha,nombre);
            data[total]=aux;
        }
        else {
            Fijo aux;
            aux.Leer(cod,fecha, nombre);
            data[total]=aux;
        }
          total++;
    }
    void Agrega(tiempo fecha, char nombre[]){
        if(total==max) crece();
         char cod[15];
        cout<<"Ingrese el Nmro de cuenta de la tarjeta a agregar: ";cin>>cod;
         int pos=buscar(cod);
         if(pos==-1) inserta(cod, fecha, nombre);
         else cout<<"El Nmro de tarjeta ya esta registrado..."<<endl;
    }
    void ListarCuentas(){
        cout<<"\tCuentas Del Clienta:"<<endl;
        for (int i = 0; i < total; ++i) {
            data[i].Presentar();
            cout<<"*********************"<<endl;
        }
    }
    void ListarEstado(){
        cout<<"\tCuentas Del Clienta:"<<endl;
        for (int i = 0; i < total; ++i) {
            data[i].ListaEstado();
            cout<<"--------------------------------------"<<endl;
        }
    }
    void ListarTipoMoneda(){
        int sol=12, dolar=12;
        gotoxy(40,sol);
        cout<<"Cuentas en Soles"<<endl;
        gotoxy(70,dolar);
        cout<<"Cuentas en Dolares"<<endl;
        for (int i = 0; i < total; ++i) {
            if(data[i].getMoneda()==1){
                sol++;
                gotoxy(40,sol);
                cout<<"Nmro Cuenta: "<<data[i].getNumCuenta()<<endl;
            }else{
                dolar++;
                gotoxy(70,dolar);
                cout<<"Nmro Cuenta: "<<data[i].getNumCuenta()<<endl;
            }
        }
    }
    void ListarFecha(){
        tiempo fecha;
        fecha.llenar();
        for (int i = 0; i < total; ++i) {
            if(data[i].getFecha().getDia()>=fecha.getDia()){
                if(data[i].getFecha().getMes()>=fecha.getMes()){
                    if(data[i].getFecha().getAnho()>=fecha.getAnho()){
                        data[i].Presentar();
                    }
                }
            }
        }
    }
    void MenuCuenta(tiempo fecha){
        char cod[15];
        cout << "Ingrese Numero de cuenta a Realizar operaciones: ";
        cin >> cod;
        int pos=buscar(cod);
        if(pos==-1)cout<<"No existe cuenta con ese numero de  cuenta"<<endl;
        else{
         if(data[pos].getEstado()!=1) cout<<"La cuenta ha sido Cancelada o Cerrada"<<endl;
           else data[pos].validarEstado(fecha);
        }
    }
    void Activar(){
        for (int i = 0; i < total; ++i) {
            data[i].Activar();
        }
    }
    int buscar(char cod[]){
        for(int i=0;i<total;i++){
            if(strcmp(cod,data[i].getNumCuenta())==0)
               return i;
        }
        return -1;
    }
    void porcentajePorEstado(){
      int tipo[4]={0,0,0,0}, filas=12;
      for (int i = 0; i < total; ++i) {
       if(data[i].getEstado()==1) tipo[1]++;
       else if(data[i].getEstado()==2)tipo[2]++;
       else if(data[i].getEstado()==3)tipo[3]++;
       }
      float porcentaje=total;
      gotoxy(30,filas); cout<<"Tipo"; gotoxy(50,filas);cout<<"Cantidad";gotoxy(70,filas);cout<<"Porcentaje"<<endl;
      for (int i = 1; i <= 3; ++i) {
          gotoxy(30,filas+i);cout<<TEst[i];gotoxy(50,filas+i); cout<<tipo[i];gotoxy(70,filas+i);cout<<tipo[i]/porcentaje*100<<"%"<<endl;
      }
    }
};

class Cliente{
    protected:
        ListaCuentas Cuentas;
        char dni[9];
        char nombre[50];
        int sexo;
        char direccion[100];
        char telefono[10];
        char ocupacion[80];
        fechaC fechaNacimiento;
    public:
        Cliente(){
            dni[0] = '\x0';
            nombre[0] = '\x0';
            sexo=0;//0=femenino, 1=masculino
            direccion[0] = '\x0';
            telefono[0] = '\x0';
            ocupacion[0] = '\x0';
        }
        char* getDni(){
            return dni;
        }
        char* getNombre(){
            return nombre;
        }
        int getSexo(){
            return sexo;
        }
        char* getDireccion(){
            return direccion;
        }
        char* getTelefono(){
            return telefono;
        }
        char* getOcupacion(){
            return ocupacion;
        }
        void lee(char auxdni[], tiempo fecha);
        void mostrar();
        void Activar(){
            Cuentas.Activar();
        }
        void ListarEstadoCuentas(){
            Cuentas.ListarEstado();
        }
        void MenuCliente(tiempo fecha){
            int op;
            do{
              system("cls");
              fecha.mostrar();
               cout<<"\tBienvenido "<<nombre<<endl
                   <<"1)Registrar Cuenta"<<endl
                   <<"2)Listar Cuentas"<<endl
                   <<"3)Listar Cuentas por tipo de moneda"<<endl
                   <<"4)Listar cuentas por una fecha especifica"<<endl
                   <<"5)Mostrar cantidad y porcentaje de cuentas seg"<<char(163)<<"n estado de la cuenta"<<endl
                   <<"6)Ingresar a  una cuenta especifica"<<endl
                   <<"7)Cerrar Sesion"<<endl;
               do{
                   cout<<"Ingrese una opcion a realizar: ";cin>>op;
               }while(op<1 || op>7);
               switch (op) {
               case 1:
                Cuentas.Agrega(fecha, nombre);
                system("pause");
                   break;
               case 2:
                Cuentas.ListarCuentas();
                system("pause");
                   break;
               case 3:
                   Cuentas.ListarTipoMoneda();
                system("pause");
                   break;
               case 4:
                   Cuentas.ListarFecha();
                system("pause");
                   break;
               case 5:
                Cuentas.porcentajePorEstado();
                system("pause");
                   break;
               case 6:
                Cuentas.MenuCuenta(fecha);
                system("pause");
                   break;
               }
            }while(op!=7);
        }
};
void Cliente::lee(char auxdni[],tiempo fecha){
    strcpy(dni,auxdni);
    cin.ignore();
    cout << "Ingrese Nombre completo del cliente: ";cin.getline(nombre,50);
    cout << "Ingrese Direccion del cliente: ";cin.getline(direccion,100);
    cout << "Ingrese Ocupacion del cliente: ";cin.getline(ocupacion,80);
    cout << "Ingrese la opcion que corresponda al sexo del cliente: "<<endl;
    for (int i = 0; i < 2; ++i) {
        cout<<i+1<<")"<<Sexo[i]<<endl;
    }
    do{
         cout<<"[1-2]: ";cin>>sexo;
     }while(sexo>2 || sexo<1);
    cout << "FECHA DE NACIMIENTO" << endl
         <<".:Debe de ser mayor de edad:."<<endl;fechaNacimiento.llenar(fecha);
    cout << "Ingrese telefono del cliente: ";cin >> telefono;
}
void Cliente::mostrar(){
    cout <<endl<< "DATOS DEL CLIENTE"<<endl;
    cout << "DNI: " << dni << endl;;
    cout << "Nombre: "<< nombre << endl;
    cout << "Sexo: " << Sexo[sexo-1] << endl;
    cout << "Fecha de nacimiento: ";fechaNacimiento.mostrar();
    cout << "Direccion: " << direccion << endl;
    cout << "Telefono: " << telefono << endl;
    cout << "Ocupacion: " << ocupacion << endl;
}
class ListaCliente{
    protected:
        Cliente *data;
        int N, Max;
    public:
        ListaCliente(){
            data = NULL;
            N=0;
            Max=0;
        }
        ~ListaCliente(){
            delete data;
            N=0;
        }
        void crece();
        void inserta(Cliente);
        void Agrega(tiempo fecha);
        void listado();
        void Activar(){
            for (int i = 0; i < N; ++i) {
                data[i].Activar();
            }
        }

        void CantidadSexo(){
            int M=0,F=0;
            for (int i = 0; i < N; ++i) {
                if(data[i].getSexo()==1) M++;
                else F++;
            }
            gotoxy(40,18);
            cout<<"Hombres: "<<M<<endl;
            gotoxy(70,18);
            cout<<"Mujeres: "<<F<<endl;
        }
        void Menu(tiempo fecha){
            char auxdni[9];
            cout << "Ingrese DNI del cliente : ";
            cin >> auxdni;
            int pos=buscar(auxdni);
            if(pos==-1) cout<<"El Cliente no esta Registrado"<<endl;
            else data[pos].MenuCliente(fecha);
        }

        int buscar(char auxdni[]){

            for(int i=0;i<N;i++){
                if(strcmp(auxdni,data[i].getDni())==0)
                   return i;
            }
            return -1;

        }
        void ListarEstado(){
            char auxdni[9];
            cout << "Ingrese DNI del cliente : ";
            cin >> auxdni;
            int pos=buscar(auxdni);
            if(pos==-1)cout<<"El cliente no Existe"<<endl;
            else data[pos].ListarEstadoCuentas();
        }
};
    void ListaCliente::crece(){
    Cliente *Temp = new Cliente[Max+DELTA];

    for(int i=0; i<N; i++)
        Temp[i]= data[i];

    delete []data;
    data = Temp;
    Max += DELTA;

}
    void ListaCliente::inserta(Cliente objC){
    if(N==Max) crece();
    data[N]=objC;
    N++;
}
    void ListaCliente::Agrega(tiempo fecha){
        Cliente C;
        char auxdni[9];
        cout << "Ingrese DNI del cliente : ";
        cin >> auxdni;
        int pos=buscar(auxdni);
        if(pos!=-1) cout<<"El Cliente ya esta registrado"<<endl;
        else{
        C.lee(auxdni,fecha);
        inserta(C);
        }
}
    void ListaCliente::listado(){
    printf("\n**CLIENTES**\n");
    if(N>0){
        for(int i=0; i<N; i++){
            printf("\nCliente Nro %d",i+1);
            data[i].mostrar();
        }
    }else
        cout << "NO HAY CLIENTES REGISTRADOS."<<endl;
}
class Banco{
    private:
     ListaCliente Clientes;
     tiempo fecha;
     char contrasena[11];
    public:
     void Bienvenida(){

         cout<<"\n\tBienvenido Jefe"<<endl
             <<"\t"<<char(173)<<"Hoy es la gran inauguracion!"<<endl
             <<"\tPor cierto...."<<endl<<"\t"<<char(168)<<"Me recuerdas que d"<<char(161)<<"a es hoy?"<<endl;
         fecha.llenar();
         cout<<"\tAh"<<char(173)<<"Cierto!, Como pude olvidarlo, bueno te dejo, eres el jefe y tienes que guardar algunos datos"<<endl
             << "\t"<<char(173)<<"Hasta pronto!"<<endl;
         system("pause");
         system("cls");
         fecha.mostrar();
         cout<<"Ahora eres el Gerente de MiFortuna, y realizaras actividades como Terminar la jornada, entre otras"<<endl
             <<"Para ello necesitaras una contrase"<<char(164)<<"a(No puede ser cambiada)"<<endl;
         cout<<"Ingrese Contrase"<<char(164)<<"a: ";cin>>contrasena;
         cout<<"Perfecto, ha empezar el primer d"<<char(161)<<"a de trabajo, mucha suerte"<<endl;
         system("pause");
     }
     void FechaActual(){
         fecha.mostrar();
     }
     void TerminarDia(){
         char aux[11];
         cout<<"Ingrese la contraseña del Banco: ";cin>>aux;
         if(strcmp(aux,contrasena)==0){
             if(fecha.getDia()==31) Clientes.Activar();
             fecha.terminarDia();
         }
         else cout<<"Contraseña Incorrenta..."<<endl;
     }

     void MenuBanco(){
         int op;
         do{
         system("cls");
         FechaActual();
         cout<<"\t\tMiFortuna"<<endl
             <<"1)Listar Clientes"<<endl
             <<"2)Registrar un Cliente"<<endl
             <<"3)Iniciar Sesion de un cliente"<<endl
             <<"4)Cantidad de Clientes por Sexo que tengan una cuenta"<<endl
             <<"5)Mostrar Cuentas de un Cliente por DNI"<<endl
             <<"6)Terminar el Dia"<<endl
             <<"7)Salir"<<endl;
         do{
             cout<<"Ingrese una Opcion: ";cin>>op;
         }while(op<1 || op>7);
         switch (op) {
         case 1:
             Clientes.listado();
             system("pause");
             break;
         case 2:
             Clientes.Agrega(fecha);
             system("pause");
             break;
         case 3:
             Clientes.Menu(fecha);
             system("pause");
             break;
         case 4:
             Clientes.CantidadSexo();
             system("pause");
             break;
         case 5:
             Clientes.ListarEstado();
             system("pause");
             break;
         case 6:
             TerminarDia();
             system("pause");
             break;
         }
     }while(op!=7);
    }
};

int main(){
    Banco MiFortuna;
    MiFortuna.Bienvenida();
    MiFortuna.MenuBanco();
    return 0;
}
