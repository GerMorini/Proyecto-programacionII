#include <iostream>
#include "clases.h"

using namespace std;

int main(int argc, char *argv[]) {
    if (argc != 1) {
        cout << "Uso: " << argv[0] << " " << endl;
        return 1;
    }

    /* TODO:
        hacer sistema de inicio de sesión
        * permitir elegir entre autor [1] o usuario [2]
        * ingresar nombre
    */

    int opt;
    NEWS medio;

    switch (opt) {
        case 1:
            string tit, det;
            Fecha f;
            Autor autor1;

            Noticia n(tit, det, f, autor1);

            medio.publicar(n);
            break;
        case 6:
            // TODO: acá se debe llamar al destructor de 'medio'
            delete &medio;
            break;
    }
}
