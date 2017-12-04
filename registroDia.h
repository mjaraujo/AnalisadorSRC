class RegistroDia {
    int dia, hora, upload;
    long long int download;
public:
    RegistroDia(int dia, long long int d, int u = 0);
    void SetUpload(int upload);
    int GetUpload() ;
    void SetDownload(long long int download);
    long long int GetDownload() ;
    void SetDia(int dia);
    int GetDia();
};
