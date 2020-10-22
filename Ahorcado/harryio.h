/**<harry inputs-outputs: biblioteca personal de ingreso y egreso de datos por teclado*/

/** Recibe el mensaje de muestra o pedido y pide un entero, si se habilita la validacion, compara el numero con los parametros
 *  maximo y minimo y mientras no se encuentre dentro del rango repite el pedido pero utilizando el mensaje de error por parametro.
 *
 * \param char msj[]      mensaje de pedido
 * \param char error[]    mensaje de error
 * \param float min       numero flotante minimo (excluido)
 * \param float max       numero flotante maximo (excluido)
 * \param int limit       flag de validacion min/max (1 para habilitar)
 * \return int num  entero ingresado por teclado
 *
 */
int getInt(char msj[],char error[],int min,int max,int limit);

/** Recibe el mensaje de muestra o pedido y pide un flotante, si se habilita la validacion, compara el numero con los parametros
 *  maximo y minimo y mientras no se encuentre dentro del rango repite el pedido pero utilizando el mensaje de error por parametro.
 *
 * \param char msj[]          mensaje de pedido
 * \param char error[]        mensaje de error
 * \param float min           numero flotante minimo (excluido)
 * \param float max           numero flotante maximo (excluido)
 * \param int limit           flag de validacion min/max (1 para habilitar)
 * \return float num    flotante ingresado por teclado
 *
 */
float getFloat(char msj[],char error[],float min,float max,int limit);

/** \ Pide ingresar un caracter por teclado y devuelve ese caracter
 *
 * \param char msj[]              mensaje de pedido
 * \param char error[]            mensaje de error
 * \param float min               caracter minimo (excluido)
 * \param float max               caracter maximo (excluido)
 * \param int limit               flag de validacion min/max (1 para habilitar)
 * \return char caracter    caracter ingresado por teclado
 */
char getChar(char msj[],char error[],char min,char max,int limite);

/** \ Pide ingresar una cadena de caracteres por teclado y la guarda en la variable de cadena de caracteres pasada por parametro
 *
 * \char string[]   cadena de caracteres donde se guardara el ingreso por teclado
 * \char msj[]      mensaje de pedido
 *
 */
void getString(char string[],char msj[]);
