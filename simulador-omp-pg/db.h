#ifndef DB_H
#define DB_H

#ifdef __cplusplus
extern "C" {
#endif

#define DBSERVER "192.168.17.126"
#define DBPORT 5432
#define DBNAME "psudb"
#define DBUSER "psu"
#define DBPASSWORD "psu"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <postgresql/libpq-fe.h>

    /**
     * Abre la conexión a la base de datos.
     * @param servidor ip del servidor postgresql
     * @param puerto puerto del servidor postgresql
     * @param nombredb nombre de la base de datos
     * @param usuario usuario para conectar
     * @param password contraseña del usuario
     * @return objeto conexión
     */
    PGconn* dbconnect(char* servidor, int puerto, char* nombredb, char* usuario, char* password);

    /**
     * Cierra la conexión a la base de datos
     * @param conexion Puntero a la conexión
     */
    void dbclose(PGconn* conexion);

    /**
     * Consulta contra la base de datos
     * @param conexion Conexión abierta al motor
     * @param consulta Consulta SQL válida
     * @return el resultado de la consulta
     */
    PGresult* dbquery(PGconn* conexion, char* consulta);

    /**
     * 
     * @param resultado Estructura con el resultado
     * @return la cantidad de filas de dicho resultado
     */
    long dbnumrows(PGresult* resultado);

    /**
     * 
     * @param resultado Estructura de resultado
     * @param fila Fila a consultar
     * @param columna Columna a obtener
     * @return El valor correspondiente a fila/columna sobre el set de resultado
     */
    char* dbresult(PGresult* resultado, int fila, int columna);

    /**
     * Libera el recurso
     * @param resultado Estructura con el resultado
     */
    void dbfree(PGresult *resultado);
#ifdef __cplusplus
}
#endif

#endif /* DB_H */

