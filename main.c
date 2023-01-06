#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include <unistd.h>

struct Publicacion {
    int id;
    char texto[100];
} typedef Publicacion;

struct Usuario
{
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

bool escribir_usuario_en_archivo(Usuario usuario);
bool crear_almacenamiento_de_usuario(Usuario usuario);
bool buscar_usuario_en_archivo(Credenciales credenciales);
bool eliminar_en_archivo(char nombre_archivo[], int id);
bool escribir_publicacion_en_archivo(char nombre_usuario[], Publicacion publicacion);

bool crear_cuenta();
char* iniciar_sesion();
bool crear_publicacion(char nombre_usuario[]);

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
    case 3: return SALIR_SESION;    
    case 4: return SALIR_PROGRAMA;    
    default: return -1;
    }
}

void mostrar_menu_usuario() {
    printf("\n\nPAGINA DE INICIO \n");
    printf("******\n");
    printf("\n1....IMPRIMIR TODAS LAS PUBLICACIONES");
    printf("\n2....INGRESAR NUEVA PUBLICACION");
    printf("\n3....SALIR DE LA SESION\n\n");
    printf("4....SALIR\n\n");
    printf(" INGRESAR ELECCION..");
}

OpcionPrincipal manejar_opciones_menu(OpcionPrincipal opcion) {
    OpcionUsuario opcion_usuario;
    char* usuario;
    switch (opcion) {
    case CREAR_CUENTA:
        if (crear_cuenta()) {
            printf("Cuenta creada con exito");
        } else {
            printf("Problemas al crear la cuenta");
        }
        break;
    case INICIAR_SESION:
        usuario = iniciar_sesion();
        printf("usuario de nuevo: %s", usuario);
        if (usuario) {
            do {
                mostrar_menu_usuario();
                int opcion_elegida; 
                scanf("%d", &opcion_elegida);
                opcion_usuario = opcion_menu_principal(opcion_elegida);
                // TODO: Checar porque el usuario no se esta pasando bien desde iniciar_sesion()
            } while (manejar_opciones_menu_usuario(opcion_usuario, "rodri") != SALIR_SESION);
        } else {
            printf("Problemas al iniciar sesion");
        }
        break;
    case SALIR:
        printf("adios");
        exit(0);
        break;
    default:
        printf("Opcion invalida");
        break;
    }

    return opcion;
}

OpcionUsuario manejar_opciones_menu_usuario(OpcionUsuario opcion, char usuario[]) {
    switch (opcion) {
    case VER_PUBLICACION:
        printf("Ver publicz");
        break;
    case CREAR_PUBLICACION:
        if( crear_publicacion(usuario)) {
            printf("Publicacion creada con exito");
        } else {
            printf("Algo fallo");
        }
        break;
    case SALIR_SESION:
        printf("Cerrando sesion");
        break;
    case SALIR_PROGRAMA:
        // TODO: Check this
        printf("adios");
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

    publicacion.id = 1;

    return publicacion;
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
    char path[200] = "";
    mkdir("usuarios");
    strcat(path, "usuarios/");
    strcat(path, usuario.nombre_usuario);
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
    return false;
}

bool escribir_publicacion_en_archivo(char nombre_usuario[], Publicacion publicacion) {
    char path[200] = "";
    strcat(path, "usuarios");
    strcat(path, nombre_usuario);
    strcat(path, "/publicaciones.txt");

    printf("nombre archivo: %s", path);

    FILE *archivo;
    archivo = fopen(path, "ab");
    if (archivo == NULL) {
        return false;
    }
    
    fwrite(&publicacion, sizeof(publicacion), 1, archivo);
    fclose(archivo);
    return true;
}

bool crear_cuenta() {
    Usuario usuario = obtener_informacion_usuario();
    // TODO: Validar que el usuario no se encuentre en la DB
    return escribir_usuario_en_archivo(usuario) && crear_almacenamiento_de_usuario(usuario);
}

char* iniciar_sesion() {
    Credenciales crendeciales = obtener_credenciales_usuario();
    // TODO: Preservar sesion/usuario si la autenticacion es exitosa
    return buscar_usuario_en_archivo(crendeciales) ? crendeciales.nombre_usuario : NULL;
}

bool crear_publicacion(char nombre_usuario[]) {
    Publicacion publicacion = obtener_publicacion();
    return escribir_publicacion_en_archivo(nombre_usuario, publicacion);
}

int main(int argc, char const *argv[])
{
    OpcionPrincipal opcion;
    do
    {
        int opcion_elegida;
        mostrar_menu_principal();
        scanf("%d", &opcion_elegida);
        opcion = opcion_menu_principal(opcion_elegida);
    } while (manejar_opciones_menu(opcion) != SALIR);
    
    return 0;
}


