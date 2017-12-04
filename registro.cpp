/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
// classes example

/**
* Author: Márcio e Luca 
*/
#include <iostream>

#include "registro.h"

using namespace std;

Registro::Registro(int dm, int ds, int h, long long int d, int u)
: diaMes(dm), diaSemana(ds), hora(h), download(d), upload(u) {

}

int Registro::GetDiaMes() {
    return diaMes;
}

int Registro::GetDiaSemana() {
    return diaSemana;
}

long long int Registro::GetDownload() {
    return download;
}

int Registro::GetHora() {
    return hora;
}

int Registro::GetUpload() {
    return upload;
}

void Registro::SetDiaMes(int dm) {
    diaMes = dm;

}
void Registro::SetDiaSemana(int ds) {
    diaSemana = ds;

}
void Registro::SetDownload(long long int dl) {
    download = dl;

}
void Registro::SetHora(int h) {
    hora = h;

}
void Registro::SetUpload(int u) {
    upload = u;

}


