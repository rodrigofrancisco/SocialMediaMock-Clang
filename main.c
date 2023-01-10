#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>

#include "social-media-core.h"
#include "almacenamiento-en-archivos.h"

OpcionPrincipal manejar_opciones_menu(OpcionPrincipal opcion);
OpcionUsuario manejar_opciones_menu_usuario(OpcionUsuario opcion, char usuario[]);

void crear_cuenta();
char* iniciar_sesion();
void manejar_sesion(char* usuario);
void crear_publicacion(char nombre_usuario[]);
void obtener_publicaciones_usuario(char nombre_usuario[]);
void eliminar_publicacion(char nombre_usuario[]);

void agregar_amigo(char nombre_usuario[]);
void ver_amigos(char nombre_usuario[]);
void ver_solicitudes(char nombre_usuario[]);
void aceptar_solicitud(char nombre_usuario[]);
void ver_publicaciones_amigos(char nombre_usuario[]);
void ver_amigos_de_amigo(char nombre_usuario[]);
void eliminar_amigo(char nombre_usuario[]);

OpcionPrincipal manejar_opciones_menu(OpcionPrincipal opcion) {
    switch (opcion) {
    case CREAR_CUENTA: crear_cuenta(); break;
    case INICIAR_SESION: manejar_sesion(iniciar_sesion()); break;
    case SALIR: salir_programa(); break;
    default: opcion_invalida(); break;
    }
    return opcion;
}

OpcionUsuario manejar_opciones_menu_usuario(OpcionUsuario opcion, char usuario[]) {
    switch (opcion) {
    case VER_PUBLICACION: obtener_publicaciones_usuario(usuario); break;
    case CREAR_PUBLICACION: crear_publicacion(usuario); break;
    case ELIMINAR_PUBLICACION: eliminar_publicacion(usuario); break;
    case AGREGAR_AMIGO: agregar_amigo(usuario); break; 
    case VER_SOLICITUDES: ver_solicitudes(usuario); break;  
    case ACEPTAR_SOLICITUD: aceptar_solicitud(usuario); break;  
    case VER_AMIGOS: ver_amigos(usuario); break;  
    case VER_PUBLICACIONES_AMIGOS: ver_publicaciones_amigos(usuario); break;
    case VER_AMIGOS_DE_AMIGO: ver_amigos_de_amigo(usuario); break;
    case SALIR_SESION: cerrar_sesion(); break;
    case SALIR_PROGRAMA: salir_programa(); break;
    default: opcion_invalida(); break;
    }
    return opcion;
}

void crear_cuenta() {
    Usuario usuario = obtener_informacion_usuario();
    char* path = construir_direccion_usuario(usuario.nombre_usuario); 
    if (!buscar_nombre_usuario_en_archivo(usuario.nombre_usuario)) {
        if(escribir_usuario_en_archivo(usuario) && 
            crear_almacenamiento_de_usuario(path)) {
            printf("Cuenta creada con exito\n");
        }
    } else {
        printf("Problemas al crear la cuenta\n");
    }
}

char* iniciar_sesion() {
    Credenciales crendeciales = obtener_credenciales_usuario();
    char* usuario = (char *)calloc(1, strlen(crendeciales.nombre_usuario) + 1);
    strcpy(usuario, crendeciales.nombre_usuario);
    return buscar_usuario_en_archivo(crendeciales) ? usuario : NULL;
}

void manejar_sesion(char* usuario) {
    OpcionUsuario opcion_usuario;
    if (usuario) {
        do {
            mostrar_menu_usuario();
            int opcion_elegida; 
            scanf("%d", &opcion_elegida);
            opcion_usuario = opcion_menu_usuario(opcion_elegida);
        } while (manejar_opciones_menu_usuario(opcion_usuario, usuario) != SALIR_SESION);
    } else {
        printf("Problemas al iniciar sesion\n");
    }
}

void crear_publicacion(char nombre_usuario[]) {
    Publicacion publicacion = obtener_publicacion();
    char* path = construir_direccion_usuario_publicaciones(nombre_usuario);
    if(escribir_publicacion_en_archivo(path, publicacion)) {
        printf("Publicacion creada con exito\n");
    } else {
        printf("Algo fallo\n");
    }
}

void obtener_publicaciones_usuario(char nombre_usuario[]) {
    char* path = construir_direccion_usuario_publicaciones(nombre_usuario);
    LinkedList* publicaciones = leer_publicaciones_en_archivo(path);
    linked_list_peeker(publicaciones);
}

void eliminar_publicacion(char nombre_usuario[]) {
    int pos = obtener_pos_publicacion();
    char* path = construir_direccion_usuario_publicaciones(nombre_usuario);
    if(eliminar_publicacion_en_archivo(path, pos)) {
        printf("Publicacion eliminada con exito\n");
    } else {
        printf("Algo fallo\n");
    }    
}

void agregar_amigo(char nombre_usuario[]) {
    Amigo amigo = obtener_nombre_usuario_amigo();
    if (buscar_nombre_usuario_en_archivo(amigo.nombre_usuario)) {
        if(crear_solicitud_amigo_en_archivo(nombre_usuario, amigo)) {
            printf("Solicitud enviada\n");
        }
    } else {
        printf("Algo fallo al enviar solicitud\n");
    }
}

void ver_amigos(char nombre_usuario[]) {
    char* path = construir_direccion_usuario_amigos(nombre_usuario);
    LinkedList_Friend* amigos = ver_amigos_en_archivo(path);
    linked_list_peeker_friend(amigos);
}

void ver_solicitudes(char nombre_usuario[]) {
    char* path = construir_direccion_usuario_solicitudes(nombre_usuario);
    LinkedList_Friend* amigos = ver_solicitudes_en_archivo(path);
    linked_list_peeker_friend(amigos);
}

void aceptar_solicitud(char nombre_usuario[]) {
    Amigo amigo = obtener_amigo_solicitud();
    if(aceptar_solicitud_en_archivos(nombre_usuario, amigo)) {
        printf("Solicitud aceptada\n");
    } else {
        printf("Algo fallo al aceptar solicitud\n");
    }
}

void ver_publicaciones_amigos(char nombre_usuario[]) {
    Amigo amigo = obtener_amigo_para_ver_publicaciones();
    char* path = construir_direccion_usuario_amigos(nombre_usuario);
    if (es_amigo_en_archivo(path, amigo)) {
        obtener_publicaciones_usuario(amigo.nombre_usuario);
    } else {
        printf("Algo salio mal, revisa la amistad\n");
    }
}

void ver_amigos_de_amigo(char nombre_usuario[]) {
    Amigo amigo = obtener_amigo_para_ver_amigos();
    char* path = construir_direccion_usuario_amigos(nombre_usuario);
    if (es_amigo_en_archivo(path, amigo)) {
        ver_amigos(amigo.nombre_usuario);
    } else {
        printf("Algo salio mal, revisa la amistad\n");
    }
}

int main(int argc, char const *argv[]) {
    OpcionPrincipal opcion;
    do {
        int opcion_elegida;
        mostrar_menu_principal();
        scanf("%d", &opcion_elegida);
        opcion = opcion_menu_principal(opcion_elegida);
    } while (manejar_opciones_menu(opcion) != SALIR);
    
    return 0;
}
