#ifndef SOCIAL_MEDIA_CORE
#define SOCIAL_MEDIA_CORE

#include <stdio.h>
#include <stdbool.h>
#include "lista-enlazada-amigos.h"
#include "lista-enlazada-publicaciones.h"

struct Usuario {
    char nombre[50];
    char nombre_usuario[50];
    char contrasena[50];
} typedef Usuario;

struct Credenciales {
    char nombre_usuario[50];
    char contrasena[50];
} typedef Credenciales;


enum OpcionPrincipal {
    CREAR_CUENTA,
    INICIAR_SESION,
    SALIR
} typedef OpcionPrincipal;

enum OpcionUsuario {
    VER_PUBLICACION,
    CREAR_PUBLICACION,
    ELIMINAR_PUBLICACION,
    AGREGAR_AMIGO,
    VER_SOLICITUDES,
    ACEPTAR_SOLICITUD,
    VER_AMIGOS,
    VER_PUBLICACIONES_AMIGOS,
    VER_AMIGOS_DE_AMIGO,
    SALIR_SESION,
    SALIR_PROGRAMA
} typedef OpcionUsuario;

void salir_programa();
void opcion_invalida();
void cerrar_sesion();
void mostrar_menu_principal();
void mostrar_menu_usuario();
OpcionPrincipal opcion_menu_principal(int opcion);
OpcionUsuario opcion_menu_usuario(int opcion);

Usuario obtener_informacion_usuario();
Credenciales obtener_credenciales_usuario();
Publicacion obtener_publicacion();
int obtener_pos_publicacion();
Amigo obtener_nombre_usuario_amigo();
Amigo obtener_amigo_solicitud();
Amigo obtener_amigo_para_ver_publicaciones();
Amigo obtener_amigo_para_ver_amigos();

void salir_programa() {
    printf("adios\n");
    exit(0);
}

void opcion_invalida() {
    printf("Opcion invalida\n");
}

void cerrar_sesion() {
    printf("Cerrando sesion\n");
}

void mostrar_menu_principal() {
    printf("\nBIENVENIDO A FWIFFER\n\n");
    printf("**********************************\n\n");
    printf("1.... CREAR NUEVA CUENTA\n");
    printf("2.... INICIAR SESION\n");
    printf("3.... SALIR\n\n");
    printf("\n\nINGRESAR ELECCION.....\t\t");
}

OpcionPrincipal opcion_menu_principal(int opcion) {
    switch (opcion) {
    case 1: return CREAR_CUENTA;
    case 2: return INICIAR_SESION;
    case 3: return SALIR;    
    default: return -1;
    }
}

OpcionUsuario opcion_menu_usuario(int opcion) {
    switch (opcion) {
    case 1: return VER_PUBLICACION;
    case 2: return CREAR_PUBLICACION;
    case 3: return ELIMINAR_PUBLICACION;
    case 4: return AGREGAR_AMIGO;
    case 5: return VER_SOLICITUDES;
    case 6: return ACEPTAR_SOLICITUD;
    case 7: return VER_AMIGOS;
    case 8: return VER_PUBLICACIONES_AMIGOS;
    case 9: return VER_AMIGOS_DE_AMIGO;
    case 10: return SALIR_SESION;    
    case 11: return SALIR_PROGRAMA;    
    default: return -1;
    }
}

void mostrar_menu_usuario() {
    printf("\n\nPAGINA DE INICIO \n");
    printf("******\n");
    printf("\n1....IMPRIMIR TODAS LAS PUBLICACIONES");
    printf("\n2....INGRESAR NUEVA PUBLICACION");
    printf("\n3....ELIMINAR PUBLICACION");
    printf("\n4....AGREGAR AMIGO");
    printf("\n5....VER SOLICITUDES");
    printf("\n6....ACEPTAR SOLICITUD");
    printf("\n7....VER AMIGOS");
    printf("\n8....VER PUBLICACIONES AMIGOS");
    printf("\n9....VER AMIGOS DE AMIGO");
    printf("\n10....SALIR DE LA SESION\n\n");
    printf("11....SALIR\n\n");
    printf(" INGRESAR ELECCION..");
}

Usuario obtener_informacion_usuario() {
    Usuario u1;

    printf("\n\n!!!!!CREAR CUENTA!!!!!");
    printf("\nNOMBRE.....\t");
    scanf("%s", &u1.nombre);

    printf("\n\nUSUARIO.....\t");
    scanf("%s", &u1.nombre_usuario);

    printf("\nPASSWORD.....\t");
    scanf("%s", &u1.contrasena);

    return u1;
}

Credenciales obtener_credenciales_usuario() {
    Credenciales c1;
    printf("\n\nINICIANDO SESION\n");
    printf("***********************************************\n");
  
    printf("USUARIO.. \t");
    scanf("%s", &c1.nombre_usuario);
   
    printf("\nPASSWORD..\t");
    scanf("%s", &c1.contrasena);

    return c1;
}

Publicacion obtener_publicacion() {
    Publicacion publicacion;
    printf("\n---- CREANDO PUBLICACION ----\n");
    printf("\n========================");
    printf("\nINGRESE LO QUE DESEA PUBLICAR..\t");
    scanf(" %[^\n]s", publicacion.texto);

    return publicacion;
}

int obtener_pos_publicacion() {
    int pos;
    printf("\nINGRESE LO QUE DESEA ELIMINAR..\t");
    scanf(" %d", &pos);

    return pos;
}

Amigo obtener_nombre_usuario_amigo() {
    Amigo amigo;
    printf("INGRESE EL NOMBRE DE USUARIO DEL AMIGO a solicitar: \t");
    scanf("%s", &amigo.nombre_usuario);

    return amigo;
}

Amigo obtener_amigo_solicitud() {
    Amigo amigo;
    printf("INGRESE EL NOMBRE DE USUARIO DEL AMIGO a aprobar: \t");
    scanf("%s", &amigo.nombre_usuario);

    return amigo;
}

Amigo obtener_amigo_para_ver_publicaciones() {
    Amigo amigo;
    printf("DE QUE AMIGO QUIERES VER LAS PUBLICACIONES: \t");
    scanf("%s", &amigo.nombre_usuario);

    return amigo;
}

Amigo obtener_amigo_para_ver_amigos() {
    Amigo amigo;
    printf("DE QUE AMIGO QUIERES VER SUS AMIGOS: \t");
    scanf("%s", &amigo.nombre_usuario);

    return amigo;
}

#endif
