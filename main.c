#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include <unistd.h>

#include "lista-enlazada-publicaciones.h"
#include "lista-enlazada-amigos.h"

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
    SALIR_SESION,
    SALIR_PROGRAMA
} typedef OpcionUsuario;

void mostrar_menu_principal();
void mostrar_menu_usuario();
OpcionPrincipal opcion_menu_principal(int opcion);
OpcionUsuario opcion_menu_usuario(int opcion);

OpcionPrincipal manejar_opciones_menu(OpcionPrincipal opcion);
OpcionUsuario manejar_opciones_menu_usuario(OpcionUsuario opcion, char usuario[]);

Usuario obtener_informacion_usuario();
Credenciales obtener_credenciales_usuario();
Publicacion obtener_publicacion();
int obtener_pos_publicacion();
Amigo obtener_nombre_usuario_amigo();
Amigo obtener_amigo_solicitud();

char* construir_direccion_usuario(char usuario[]);
char* construir_direccion_usuario_publicaciones(char usuario[]);
char* construir_direccion_usuario_amigos(char usuario[]);
char* construir_direccion_usuario_solicitudes(char usuario[]);
bool escribir_usuario_en_archivo(Usuario usuario);
bool crear_almacenamiento_de_usuario(Usuario usuario);
bool buscar_usuario_en_archivo(Credenciales credenciales);
bool buscar_nombre_usuario_en_archivo(char nombre_usuario[]);
bool escribir_publicacion_en_archivo(char nombre_usuario[], Publicacion publicacion);
LinkedList* leer_publicaciones_en_archivo(char nombre_usuario[]);
bool eliminar_publicacion_en_archivo(char nombre_usuario[], int id); 
bool crear_solicitud_amigo_en_archivo(char nombre_usuario[], Amigo amigo);
bool eliminar_solicitud_amigo_en_archivo(char nombre_usuario[], Amigo amigo);
LinkedList_Friend* ver_amigos_en_archivo(char nombre_usuario[]);
bool agregar_amigo_en_archivo(char nombre_usuario[], Amigo amigo);
LinkedList_Friend* ver_solicitudes_en_archivo(char nombre_usuario[]);
bool aceptar_solicitud_en_archivos(char nombre_usuario[], Amigo amigo);

bool crear_cuenta();
char* iniciar_sesion();
void manejar_sesion(char* usuario);
bool crear_publicacion(char nombre_usuario[]);
void obtener_publicaciones_usuario(char nombre_usuario[]);
bool eliminar_publicacion(char nombre_usuario[]);

bool agregar_amigo(char nombre_usuario[]);
void ver_amigos(char nombre_usuario[]);
void ver_solicitudes(char nombre_usuario[]);
bool aceptar_solicitud(char nombre_usuario[]);
void eliminar_amigo(char nombre_usuario[]);
void ver_publicaciones_amigos(char nombre_usuario[]);
void ver_amigos_de_amigo(char nombre_usuario[]);

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
    case 7: return SALIR_SESION;    
    case 8: return SALIR_PROGRAMA;    
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
    printf("\n7....SALIR DE LA SESION\n\n");
    printf("8....SALIR\n\n");
    printf(" INGRESAR ELECCION..");
}

OpcionPrincipal manejar_opciones_menu(OpcionPrincipal opcion) {
    switch (opcion) {
    case CREAR_CUENTA:
        if (crear_cuenta()) {
            printf("Cuenta creada con exito\n");
        } else {
            printf("Problemas al crear la cuenta\n");
        }
        break;
    case INICIAR_SESION:
        manejar_sesion(iniciar_sesion());
        break;
    case SALIR:
        printf("adios\n");
        exit(0);
        break;
    default:
        printf("Opcion invalida\n");
        break;
    }

    return opcion;
}

OpcionUsuario manejar_opciones_menu_usuario(OpcionUsuario opcion, char usuario[]) {
    switch (opcion) {
    case VER_PUBLICACION:
        obtener_publicaciones_usuario(usuario);
        break;
    case CREAR_PUBLICACION:
        if(crear_publicacion(usuario)) {
            printf("Publicacion creada con exito\n");
        } else {
            printf("Algo fallo\n");
        }
        break;
    case ELIMINAR_PUBLICACION:
        if(eliminar_publicacion(usuario)) {
            printf("Publicacion eliminada con exito\n");
        } else {
            printf("Algo fallo\n");
        }
        break;
    case AGREGAR_AMIGO:
        if(agregar_amigo(usuario)) {
            printf("Solicitud enviada\n");
        } else {
            printf("Algo fallo al enviar solicitud\n");
        }
        break; 
    case VER_SOLICITUDES:
        ver_solicitudes(usuario);
        break;  
    case ACEPTAR_SOLICITUD:
        if(aceptar_solicitud(usuario)) {
            printf("Solicitud aceptada\n");
        } else {
            printf("Algo fallo al aceptar solicitud\n");
        }
        break;  
    case SALIR_SESION:
        printf("Cerrando sesion\n");
        break;
    case SALIR_PROGRAMA:
        // TODO: Check this
        printf("adios\n");
        exit(0);
        break;
    default:
        break;
    }
    return opcion;
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

char* construir_direccion_usuario(char usuario[]) {
    char path[200] = "";
    strcat(path, "usuarios/");
    strcat(path, usuario);

    char* path_pointer = (char*)calloc(1, strlen(path) + 1);
    strcpy(path_pointer, path);

    return path_pointer;
}

char* construir_direccion_usuario_publicaciones(char usuario[]) {
    char* path = construir_direccion_usuario(usuario);
    char publicaciones[] = "/publicaciones.txt";
    char* publicaciones_pointer = (char*)calloc(1, strlen(path) + 1);
    strcpy(publicaciones_pointer, publicaciones);
    strcat(path, publicaciones_pointer);
    return path;   
}

char* construir_direccion_usuario_amigos(char usuario[]) {
    char* path = construir_direccion_usuario(usuario);
    char publicaciones[] = "/amigos.txt";
    char* publicaciones_pointer = (char*)calloc(1, strlen(path) + 1);
    strcpy(publicaciones_pointer, publicaciones);
    strcat(path, publicaciones_pointer);
    return path;
}

char* construir_direccion_usuario_solicitudes(char usuario[]) {
    char* path = construir_direccion_usuario(usuario);
    char publicaciones[] = "/solicitudes.txt";
    char* publicaciones_pointer = (char*)calloc(1, strlen(path) + 1);
    strcpy(publicaciones_pointer, publicaciones);
    strcat(path, publicaciones_pointer);
    return path;   
}

bool escribir_usuario_en_archivo(Usuario usuario) {
    char nombre_archivo[] = "usuarios.txt";
    FILE *archivo_usuarios;
    archivo_usuarios = fopen(nombre_archivo, "ab");
    if (archivo_usuarios == NULL) {
        return false;
    }
    
    fwrite(&usuario, sizeof(usuario), 1, archivo_usuarios);
    fclose(archivo_usuarios);
    return true;
}

bool crear_almacenamiento_de_usuario(Usuario usuario) {
    char* path = construir_direccion_usuario(usuario.nombre_usuario); 
    mkdir("usuarios");
    return !mkdir(path);
}

bool buscar_usuario_en_archivo(Credenciales credenciales) {
    char nombre_archivo[] = "usuarios.txt";
    FILE *archivo_usuarios;
    archivo_usuarios = fopen(nombre_archivo, "rb");
    if (archivo_usuarios == NULL) {
        return false;
    }

    Usuario usuario_it;

    while (fread(&usuario_it, sizeof(usuario_it), 1, archivo_usuarios)) {
        if (strcmp(credenciales.nombre_usuario, usuario_it.nombre_usuario) == 0 && 
            strcmp(credenciales.contrasena, usuario_it.contrasena) == 0) {
            return true;
        }  
    }  
    fclose(archivo_usuarios);
    return false;
}

bool buscar_nombre_usuario_en_archivo(char nombre_usuario[]) {
    char nombre_archivo[] = "usuarios.txt";
    FILE *archivo_usuarios;
    archivo_usuarios = fopen(nombre_archivo, "rb");
    if (archivo_usuarios == NULL) {
        return false;
    }

    Usuario usuario_it;

    while (fread(&usuario_it, sizeof(usuario_it), 1, archivo_usuarios)) {
        if (strcmp(nombre_usuario, usuario_it.nombre_usuario) == 0) {
            return true;
        }  
    }  

    fclose(archivo_usuarios);
    return false;
}

bool escribir_publicacion_en_archivo(char nombre_usuario[], Publicacion publicacion) {
    char* path = construir_direccion_usuario_publicaciones(nombre_usuario); 

    FILE *archivo;
    archivo = fopen(path, "ab");
    if (archivo == NULL) {
        return false;
    }
    
    fwrite(&publicacion, sizeof(publicacion), 1, archivo);
    fclose(archivo);
    return true;
}

LinkedList* leer_publicaciones_en_archivo(char nombre_usuario[]) {
    char* path = construir_direccion_usuario_publicaciones(nombre_usuario);

    FILE *archivo;
    archivo = fopen(path, "rb");
    if (archivo == NULL) {
        return NULL;
    }

    LinkedList* publicaciones = linked_list_constructor();
    Publicacion publicacion_it;
    while (fread(&publicacion_it, sizeof(publicacion_it), 1, archivo)) {
        linked_list_insert(publicaciones, publicacion_it);
    }  

    fclose(archivo);
    return publicaciones;
}

bool eliminar_publicacion_en_archivo(char nombre_usuario[], int pos) {
    char* path = construir_direccion_usuario_publicaciones(nombre_usuario);
    char* path_tmp = construir_direccion_usuario_publicaciones(nombre_usuario);

    strcat(path_tmp, ".copy");

    FILE *archivo, *archivo_tmp;
    archivo = fopen(path, "rb");
    if (archivo == NULL) {
        return false;
    }

    archivo_tmp = fopen(path_tmp, "wb");
    if (archivo_tmp == NULL) {
        return false;
    }

    Publicacion publicacion_it;
    int it = 0;
    bool deleted_sucessfully = false;
    while (fread(&publicacion_it, sizeof(publicacion_it), 1, archivo)) {
        if (it != (pos - 1)) {
            fwrite(&publicacion_it, sizeof(publicacion_it), 1, archivo_tmp);
        } else {
            deleted_sucessfully = true;
        }
        it++;
    }  

    fclose(archivo);
    fclose(archivo_tmp);

    remove(path);
	rename(path_tmp, path);

    return deleted_sucessfully;
}

bool crear_solicitud_amigo_en_archivo(char nombre_usuario[], Amigo amigo) {
    char* path_amigo = construir_direccion_usuario_solicitudes(amigo.nombre_usuario); 

    FILE *archivo;
    archivo = fopen(path_amigo, "ab");
    if (archivo == NULL) {
        return false;
    }

    Amigo amigo_usuario;
    strcpy(amigo_usuario.nombre_usuario, nombre_usuario);
    
    fwrite(&amigo_usuario, sizeof(amigo_usuario), 1, archivo);
    fclose(archivo);

    return true;
}

bool eliminar_solicitud_amigo_en_archivo(char nombre_usuario[], Amigo amigo) {
    char* path = construir_direccion_usuario_solicitudes(nombre_usuario);
    char* path_tmp = construir_direccion_usuario_solicitudes(nombre_usuario);

    strcat(path_tmp, ".copy");

    FILE *archivo, *archivo_tmp;
    archivo = fopen(path, "rb");
    if (archivo == NULL) {
        return false;
    }

    archivo_tmp = fopen(path_tmp, "wb");
    if (archivo_tmp == NULL) {
        return false;
    }

    Amigo amigo_it;
    bool deleted_sucessfully = false;
    while (fread(&amigo_it, sizeof(amigo_it), 1, archivo)) {
        if (strcmp(amigo_it.nombre_usuario, amigo.nombre_usuario) != 0) {
            fwrite(&amigo_it, sizeof(amigo_it), 1, archivo_tmp);
        } else {
            deleted_sucessfully = true;
        }
    }  

    fclose(archivo);
    fclose(archivo_tmp);

    remove(path);
	rename(path_tmp, path);

    return deleted_sucessfully;
}


LinkedList_Friend* ver_amigos_en_archivo(char nombre_usuario[]) {
    char* path = construir_direccion_usuario_amigos(nombre_usuario);

    FILE *archivo;
    archivo = fopen(path, "rb");
    if (archivo == NULL) {
        return NULL;
    }

    LinkedList_Friend* amigos = linked_list_constructor_friend();
    Amigo amigo_it;
    while (fread(&amigo_it, sizeof(amigo_it), 1, archivo)) {
        linked_list_insert_friend(amigos, amigo_it);
    }  

    fclose(archivo);
    return amigos;
}

bool agregar_amigo_en_archivo(char nombre_usuario[], Amigo amigo) {
    char* path_amigo = construir_direccion_usuario_amigos(amigo.nombre_usuario); 

    FILE *archivo;
    archivo = fopen(path_amigo, "ab");
    if (archivo == NULL) {
        return false;
    }

    Amigo amigo_usuario;
    strcpy(amigo.nombre_usuario, nombre_usuario);
    
    fwrite(&amigo_usuario, sizeof(amigo_usuario), 1, archivo);
    fclose(archivo);

    return true;
}


LinkedList_Friend* ver_solicitudes_en_archivo(char nombre_usuario[]) {
    char* path = construir_direccion_usuario_solicitudes(nombre_usuario);

    FILE *archivo;
    archivo = fopen(path, "rb");
    if (archivo == NULL) {
        return NULL;
    }

    LinkedList_Friend* amigos = linked_list_constructor_friend();
    Amigo amigo_it;
    while (fread(&amigo_it, sizeof(amigo_it), 1, archivo)) {
        linked_list_insert_friend(amigos, amigo_it);
    }  

    fclose(archivo);
    return amigos;
}

bool aceptar_solicitud_en_archivos(char nombre_usuario[], Amigo amigo) {
    Amigo amigo_usuario;
    strcpy(amigo_usuario.nombre_usuario, nombre_usuario);
    return eliminar_solicitud_amigo_en_archivo(nombre_usuario, amigo) &&
           agregar_amigo_en_archivo(nombre_usuario, amigo) &&
           agregar_amigo_en_archivo(amigo.nombre_usuario, amigo_usuario);
}

bool crear_cuenta() {
    Usuario usuario = obtener_informacion_usuario();
    if (!buscar_nombre_usuario_en_archivo(usuario.nombre_usuario)) {
        return escribir_usuario_en_archivo(usuario) && crear_almacenamiento_de_usuario(usuario);
    } else {
        return false;
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

bool crear_publicacion(char nombre_usuario[]) {
    Publicacion publicacion = obtener_publicacion();
    return escribir_publicacion_en_archivo(nombre_usuario, publicacion);
}

void obtener_publicaciones_usuario(char nombre_usuario[]) {
    LinkedList* publicaciones = leer_publicaciones_en_archivo(nombre_usuario);
    linked_list_peeker(publicaciones);
}

bool eliminar_publicacion(char nombre_usuario[]) {
    int pos = obtener_pos_publicacion();
    return eliminar_publicacion_en_archivo(nombre_usuario, pos);
}

bool agregar_amigo(char nombre_usuario[]) {
    Amigo amigo = obtener_nombre_usuario_amigo();
    if (buscar_nombre_usuario_en_archivo(amigo.nombre_usuario)) {
        return crear_solicitud_amigo_en_archivo(nombre_usuario, amigo);
    } else {
        return false;
    }
}

void ver_amigos(char nombre_usuario[]) {
    LinkedList_Friend* amigos = ver_amigos_en_archivo(nombre_usuario);
    linked_list_peeker_friend(amigos);
}

void ver_solicitudes(char nombre_usuario[]) {
    LinkedList_Friend* amigos = ver_solicitudes_en_archivo(nombre_usuario);
    linked_list_peeker_friend(amigos);
}

bool aceptar_solicitud(char nombre_usuario[]) {
    Amigo amigo = obtener_amigo_solicitud();
    return aceptar_solicitud_en_archivos(nombre_usuario, amigo);
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


