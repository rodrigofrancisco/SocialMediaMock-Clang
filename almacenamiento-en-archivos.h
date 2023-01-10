#ifndef FRIEND_STORAGE
#define FRIEND_STORAGE

#include <stdio.h>
#include <stdbool.h>

char* construir_direccion_usuario(char usuario[]);
char* construir_direccion_usuario_publicaciones(char usuario[]);
char* construir_direccion_usuario_amigos(char usuario[]);
char* construir_direccion_usuario_solicitudes(char usuario[]);

bool escribir_usuario_en_archivo(Usuario usuario);
bool crear_almacenamiento_de_usuario(char* path);
bool buscar_usuario_en_archivo(Credenciales credenciales);
bool buscar_nombre_usuario_en_archivo(char nombre_usuario[]);
bool es_amigo_en_archivo(char* path, Amigo amigo);
bool escribir_publicacion_en_archivo(char* path, Publicacion publicacion);
LinkedList* leer_publicaciones_en_archivo(char* path);
bool eliminar_publicacion_en_archivo(char* path, int id); 
bool crear_solicitud_amigo_en_archivo(char nombre_usuario[], Amigo amigo);
bool eliminar_solicitud_amigo_en_archivo(char nombre_usuario[], Amigo amigo);
LinkedList_Friend* ver_amigos_en_archivo(char* path);
bool agregar_amigo_en_archivo(char nombre_usuario[], Amigo amigo);
LinkedList_Friend* ver_solicitudes_en_archivo(char nombre_usuario[]);
bool aceptar_solicitud_en_archivos(char nombre_usuario[], Amigo amigo);

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

bool crear_almacenamiento_de_usuario(char* path) {
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

bool es_amigo_en_archivo(char* path, Amigo amigo) {
    FILE *archivo_usuarios;
    archivo_usuarios = fopen(path, "rb");
    if (archivo_usuarios == NULL) {
        return false;
    }

    Amigo amigo_it;

    while (fread(&amigo_it, sizeof(amigo_it), 1, archivo_usuarios)) {
        if (strcmp(amigo.nombre_usuario, amigo_it.nombre_usuario) == 0) {
            return true;
        }  
    }  

    fclose(archivo_usuarios);
    return false;
}


bool escribir_publicacion_en_archivo(char* path, Publicacion publicacion) {
    FILE *archivo;
    archivo = fopen(path, "ab");
    if (archivo == NULL) {
        return false;
    }
    
    fwrite(&publicacion, sizeof(publicacion), 1, archivo);
    fclose(archivo);
    return true;
}

LinkedList* leer_publicaciones_en_archivo(char* path) {
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

bool eliminar_publicacion_en_archivo(char* path, int pos) {
    char* path_tmp = strcpy(path_tmp, path);

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

LinkedList_Friend* ver_amigos_en_archivo(char* path) {
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
    char* path = construir_direccion_usuario_amigos(nombre_usuario); 

    FILE *archivo;
    archivo = fopen(path, "ab");
    if (archivo == NULL) {
        return false;
    }

    fwrite(&amigo, sizeof(amigo), 1, archivo);
    fclose(archivo);

    return true;
}

LinkedList_Friend* ver_solicitudes_en_archivo(char* path) {
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

#endif /*END FRIEND_STORAGE*/
