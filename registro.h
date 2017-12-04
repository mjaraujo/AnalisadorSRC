class Registro {
    int diaMes, diaSemana, hora, upload;
    long long int download;
public:
    Registro(int dm, int ds, int h, long long int d, int u = 0);
    void SetUpload(int upload);
    int GetUpload() ;
    void SetDownload(long long int download);
    long long int GetDownload() ;
    void SetHora(int hora);
    int GetHora() ;
    void SetDiaSemana(int diaSemana);
    void SetDiaMes(int diaMes);
    int GetDiaSemana() ;
    int GetDiaMes();
};
