class Programa {
    private :
        int largo_operaciones ;
        char * puntero_operaciones ;
        int * puntero_salida ;
        char * operaciones ;
    public :
        Programa ( int largo_operaciones );
        void ejecutar_operador () ;
        void mover ( char dir );
        void asignar ( int valor , int * salida );
        char obtener () ;
        void terminar_programa () ;
        void ejecutar () ;
};
