/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: Márcio e Luca
 *
 * Created on 27 de Novembro de 2017, 10:16
 */

#include <cstdlib>
#include <iostream>
#include <vector>
#include <iomanip>
#include <sstream>
#include <fstream>
#include <unistd.h>
#include <complex>

#include "pthread.h"
#include "registro.h"
#include "registroDia.h"



using namespace std;
vector<RegistroDia> mediasDiaMes;
vector<RegistroDia> mediasDiaSemana;
int qtDiasMes[30];
int qtDiasSem[7];

const vector<string> explode(const string& s, const char& c);

void *monitorarE1(void *ptr) {
    int sair = 20;
    int diaM, diaS, hr, dld, upl;
    float difDldD, difUplD;
    float difDldS, difUplS;
    float c1 = 0.5, c2 = -0.5;
    float c3 = .5, c4 = -0.5, m[2], l[2], gct, gc;
    int s1, s2a, s2b;
    int V = 0, F = 1, T = 2, P = 3;
    std::string res[4] = {"VERDADEIRO", "FALSO", "INCONSISTENTE", "PARA COMPLETO"};

    do {
        ifstream arquivo("momento.txt", std::ifstream::in);
        std::string linha;
        int nlinha = 1;
        if (arquivo.good()) {
            while (std::getline(arquivo, linha)) {
                cout << "*******************LINHA: " << nlinha << endl;
                nlinha++;
                vector<string> v = explode(linha, ';');
                std::stringstream str0(v[0]);
                std::stringstream str1(v[1]);
                std::stringstream str2(v[2]);
                std::stringstream str3(v[3]);
                std::stringstream str4(v[4]);
                str0 >> diaM;
                str1 >> diaS;
                str2 >> hr;
                str3 >> dld;
                str4 >> upl;

                //calculo nova media do mes com base em novas entradas
                qtDiasMes[diaM - 1]++;
                float novoDesvMedia = (dld - mediasDiaMes[diaM - 1].GetDownload()) / qtDiasMes[diaM - 1];
                mediasDiaMes[diaM - 1].SetDownload(mediasDiaMes[diaM - 1].GetDownload() + novoDesvMedia);
                
                //calculo nova media da semana com base em novas entradas
                qtDiasSem[diaS - 1]++;
                novoDesvMedia = (dld - mediasDiaSemana[diaS - 1].GetDownload()) / qtDiasSem[diaS - 1];
                mediasDiaSemana[diaS - 1].SetDownload(mediasDiaSemana[diaM - 1].GetDownload() + novoDesvMedia);
                
                //mediasDiaMes

                difDldD = mediasDiaMes[diaM - 1].GetDownload() - dld;
                difUplD = mediasDiaMes[diaM - 1].GetUpload() - upl;

                difDldS = mediasDiaSemana[diaS].GetDownload() - dld;
                difUplS = mediasDiaMes[diaS].GetUpload() - upl;


                cout << "Media download desse dia (MES/SEMANA): (" << mediasDiaMes[diaM - 1].GetDownload() <<
                        "/" << mediasDiaSemana[diaS].GetDownload() << ")" << endl;
                cout << "Diferenca (MES/SEMANA) : (" << abs(mediasDiaMes[diaM].GetDownload() - dld) <<
                        "/" << abs(mediasDiaSemana[diaS].GetDownload() - dld) << ")" << endl;

                cout << "Media upload desse dia (MES/SEMANA): (" << mediasDiaMes[diaM - 1].GetUpload() <<
                        "/" << mediasDiaSemana[diaS].GetUpload() << ")" << endl;
                cout << "Diferenca (MES/SEMANA) : (" << abs(mediasDiaMes[diaM].GetUpload() - dld) <<
                        "/" << abs(mediasDiaSemana[diaS].GetUpload() - dld) << ")" << endl;
                cout << "M ==== Analise de download " << endl;

                //Analise de download conforme dia do mes
                float difer = abs(mediasDiaMes[diaM].GetDownload() - dld);
                m[0] = (mediasDiaMes[diaM].GetDownload() - difer) / mediasDiaMes[diaM].GetDownload();
                m[0] = m[0] < 0 ? 1 : 1 - m[0]; //se m < 0 significa que download atual supera 100% da média esperada
                cout << "mediaMes: " << mediasDiaMes[diaM].GetDownload() << " dld: " << dld << endl;

                //M ==== Analise de download conforme dia da semana
                difer = abs(mediasDiaSemana[diaS].GetDownload() - dld);
                m[1] = (mediasDiaSemana[diaS].GetDownload() - difer) / mediasDiaSemana[diaS].GetDownload();
                m[1] = m[1] < 0 ? 1 : 1 - m[1]; //se m < 0 significa que download atual supera 100% da média esperada
                cout << "mediaSemana: " << mediasDiaSemana[diaS].GetDownload() << " dld: " << dld << endl;
                cout << "m do Mes: " << m[0] << " m da Semana: " << m[1] << endl;
                
                //verifica se está ocorrendo ataque considerando a hipótese otimista em relação ao download
                m[0] = m[0] > m[1] ? m[1] : m[0];
                cout << "M: " << m[0] << endl;


                cout << "L ==== Analise de upload" << endl;

                //L ==== Analise de UPLOAD conforme dia do mes
                difer = abs(mediasDiaMes[diaM].GetUpload() - upl);
                l[0] = (mediasDiaMes[diaM].GetUpload() - difer) / mediasDiaMes[diaM].GetUpload();
                l[0] = l[0] < 0 ? 0 : 1 - l[0]; //se m < 0 significa que upload atual supera 100% da média esperada
                cout << "mediaMes: " << mediasDiaMes[diaM].GetUpload() << " upl: " << upl << endl;

                //Analise de UPLOAD conforme dia da semana
                difer = abs(mediasDiaSemana[diaS].GetUpload() - upl);
                l[1] = (mediasDiaSemana[diaS].GetUpload() - difer) / mediasDiaSemana[diaS].GetUpload();
                
                //verifica se está ocorrendo ataque considerando a hipótese otimista em relação ao upload
                l[1] = l[1] < 0 ? 0 : 1 - l[1]; //se m < 0 significa que upload atual supera 100% da média esperada
                cout << "mediaSemana: " << mediasDiaSemana[diaS].GetUpload() << " upl: " << upl << endl;

                cout << "l do Mes: " << l[0] << " l da Semana: " << l[1] << endl;
                l[0] = l[0] < l[1] ? l[1] : l[0];
                cout << "L: " << l[0] << endl;
                l[0] = l[0];
                l[0] = 1 - l[0];
               
                //Aplicação do Algoritmo "PARA-ANALISADOR"
                gct = m[0] + l[0] - 1.0;
                gc = m[0] - l[0];

                cout << gc << "|" << gct << endl;

                if (gc >= c1) {
                    s1 = V;
                }
                if (gc <= c2) {
                    s1 = F;
                }
                if (gct >= c3) {
                    s1 = T;
                }
                if (gct <= c4) {
                    s1 = P;
                }

                cout << "Resultado: " << res[s1] << endl;


                //
                usleep(1200000);
            }
            arquivo.close();
        }
    } while (1 != 0);

}

/*
 * Splita o vetor conforme o ; 
 */
const vector<string> explode(const string& s, const char& c) {
    string buff = "";
    vector<string> v;

    for (int i = 0; i < s.size(); i++) {
        if (s.at(i) != c) buff += s.at(i);
        else
            if (s.at(i) == c && buff != "") {
            v.push_back(buff);
            buff = "";
        }
    }
    if (buff != "") v.push_back(buff);

    return v;
}

int main(int argc, char** argv) {


    std::string linha;


    vector<Registro> registros;

    // leitura do histórico gerado para preencher a base
    int k = 0;
    while (std::getline(std::cin, linha)) {
        if (linha == "") continue;
        vector<string> v = explode(linha, ';');

        std::stringstream str(v[0]);
        int ddm;
        str >> ddm;

        std::stringstream str1(v[1]);
        int dds;
        str1 >> dds;

        std::stringstream str2(v[2]);
        int hr;
        str2 >> hr;

        std::stringstream str3(v[3]);
        int dl;
        str3 >> dl;

        std::stringstream str4(v[4]);
        int upl;
        str4 >> upl;

        // cout << dl << endl;
        Registro *r = new Registro(ddm, dds, hr, dl, upl);
        registros.push_back(*r);
        k++;
    }


    float diasMesD[30];
    float diasMesU[30];
    float diasSemanaD[7];
    float diasSemanaU[7];
    for (int i = 0; i < 30; i++)diasMesD[i] = 0.0;
    for (int i = 0; i < 30; i++)diasMesU[i] = 0.0;
    for (int i = 0; i < 7; i++)diasSemanaD[i] = 0.0;
    for (int i = 0; i < 30; i++)qtDiasMes[i] = 0;
    for (int i = 0; i < 7; i++)qtDiasSem[i] = 0;
    for (int i = 0; i < 7; i++)diasSemanaU[i] = 0.0;
    for (int i = 0; i < registros.size(); i++) {
        qtDiasMes[registros[i].GetDiaMes() - 1]++;
        qtDiasSem[registros[i].GetDiaSemana()]++;

    }

    cout << "DIAS DO MÊS" << endl;
    for (int i = 0; i < 30; i++) {
        cout << "Dia " << i + 1 << ": " << qtDiasMes[i] << endl;
    }



    cout << "DIAS DA SEMANA" << endl;
    for (int i = 0; i < 7; i++) {
        cout << "Dia " << i << ": " << qtDiasSem[i] << endl;
    }

    for (int i = 0; i < registros.size(); i++) {
        diasMesD[registros[i].GetDiaMes() - 1] += (float) registros[i].GetDownload();
        diasMesU[registros[i].GetDiaMes() - 1] += (float) registros[i].GetUpload();
        diasSemanaD[registros[i].GetDiaSemana()] += registros[i].GetDownload() / qtDiasSem[registros[i].GetDiaSemana() ];
        diasSemanaU[registros[i].GetDiaSemana()] += registros[i].GetUpload() / qtDiasSem[registros[i].GetDiaSemana() ];
    }

    for (int i = 0; i < 30; i++) {
        cout << diasMesD[i] << endl;
        diasMesD[i] = (float) diasMesD[i] / (float) qtDiasMes[i];
        diasMesU[i] = (float) diasMesU[i] / (float)qtDiasMes[i];
    }


    cout << "MÉDIAS POR DIA NO MES" << endl;
    cout << "DIA\tDownload\t\tUpload" << endl;
    for (int i = 0; i < 30; i++) {
        cout << i + 1 << "\t" << std::fixed << std::setw(11) << std::setprecision(4) << diasMesD[i] << " bits\t"
                << diasMesU[i] << " bits" << endl;

        RegistroDia *rd = new RegistroDia(i, diasMesD[i], diasMesU[i]);
        mediasDiaMes.push_back(*rd);
    }
    cout << endl << "MEDIAS POR DIA DA SEMANA" << endl;
    cout << "DIA\tDownload\t\tUpload" << endl;
    for (int i = 0; i < 7; i++) {
        cout << i + 1 << "\t" << diasSemanaD[i] << " bits\t\t"
                << diasSemanaU[i] << " bits" << endl;

        RegistroDia *rs = new RegistroDia(i, diasSemanaD[i], diasSemanaU[i]);
        mediasDiaSemana.push_back(*rs);
    }

    pthread_t thread1;
    char *message1 = "Thread 1";
    std::string message2 = "Thread 2";
    int iret1 = pthread_create(&thread1, NULL, monitorarE1, (void*) message1);

    pthread_join(thread1, NULL);



    return 0;
}
