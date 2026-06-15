// Fill out your copyright notice in the Description page of Project Settings.


#include "ObjetoEscaneable.h"

AObjetoEscaneable::AObjetoEscaneable()
{
    DatosEscaneo.Nombre = "Objeto Desconocido";
    DatosEscaneo.Descripcion = "Sin descripcion.";
    DatosEscaneo.Tipo = "Desconocido";
    DatosEscaneo.TiempoEscaneo = 2.f;
}

FScanData AObjetoEscaneable::GetScanData() const
{
    return DatosEscaneo;
}
