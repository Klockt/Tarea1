class Interprete {
    private :
        int cant_programas ;
        int largo_salida ;
        int cargado ;
        Programa * programas ;
        int * salida ;
    public :
        Interprete (int cant_programas , int largo_salidas);
        void cargar_programa (int n);
        void ejecutar_programa () ;
        void mostrar_programa_cargado () ;
        void terminar_ejecucion () ;
};
