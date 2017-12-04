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

#include "registroDia.h"
#include "registro.h"

using namespace std;

RegistroDia::RegistroDia(int dia, long long int d, int u)
: dia(d), download(d), upload(u) {

}

int RegistroDia::GetDia() {
    return dia;
}

long long int RegistroDia::GetDownload() {
    return download;
}


int RegistroDia::GetUpload() {
    return upload;
}

void RegistroDia::SetDia(int d) {
    dia = d;

}


void RegistroDia::SetDownload(long long int dl) {
    download = dl;
}



void RegistroDia::SetUpload(int u) {
    upload = u;

}


