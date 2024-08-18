class Programa {
    private :
        int largo_operaciones ;
        int * puntero_operaciones ;
        int * puntero_salida ;
        char * operaciones ;
    public :
        void ejecutar_operador () ;
        void mover ( char dir );
        void asignar ( int valor , int * salida );
        char obtener () ;
        void terminar_programa () ;
        Programa ( int largo_operaciones , int largo_resultado );
        void ejecutar () ;
};
