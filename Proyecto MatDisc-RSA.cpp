#include <iostream>
#include <cmath>

using namespace std;

// Función para calcular el Máximo Común Divisor (MCD)
int mcd(int a, int b) {
    if (b == 0)
        return a;
    return mcd(b, a % b);
}

// Función para encontrar el inverso modular usando el Algoritmo de Euclides Extendido
int inverso_modular(int e, int phi) {
    int t = 0, nuevo_t = 1;
    int r = phi, nuevo_r = e;

    while (nuevo_r != 0) {
        int cociente = r / nuevo_r;
        int temp = nuevo_t;
        nuevo_t = t - cociente * nuevo_t;
        t = temp;

        temp = nuevo_r;
        nuevo_r = r - cociente * nuevo_r;
        r = temp;
    }

    if (r > 1) return -1; // No existe inverso
    if (t < 0) t += phi;

    return t;
}

// Función para cifrar el mensaje
int cifrar(int mensaje, int e, int n) {
    long long resultado = 1;
    for (int i = 0; i < e; i++) {
        resultado = (resultado * mensaje) % n;
    }
    return resultado;
}

// Función para descifrar el mensaje
int descifrar(int cifrado, int d, int n) {
    long long resultado = 1;
    for (int i = 0; i < d; i++) {
        resultado = (resultado * cifrado) % n;
    }
    return resultado;
}

// Función principal
int main() {
    int p, q;
    cout << "Ingresa dos numeros primos: ";
    cin >> p >> q;

    int n = p * q;
    int phi = (p - 1) * (q - 1);

    int e;
    cout << "Ingresa un numero e (debe ser coprimo con " << phi << "): ";
    cin >> e;

    // Validar que e sea coprimo con phi
    while (mcd(e, phi) != 1) {
        cout << "e no es coprimo con " << phi << ", ingresa otro: ";
        cin >> e;
    }

    int d = inverso_modular(e, phi);
    if (d == -1) {
        cout << "No se pudo encontrar el inverso modular." << endl;
        return 1;
    }

    cout << "\nClave publica (e, n): (" << e << ", " << n << ")" << endl;
    cout << "Clave privada (d, n): (" << d << ", " << n << ")" << endl;

    int mensaje;
    cout << "\nIngresa el mensaje a cifrar (numero entero): ";
    cin >> mensaje;

    int mensaje_cifrado = cifrar(mensaje, e, n);
    cout << "Mensaje cifrado: " << mensaje_cifrado << endl;

    int mensaje_descifrado = descifrar(mensaje_cifrado, d, n);
    cout << "Mensaje descifrado: " << mensaje_descifrado << endl;

    return 0;
}

