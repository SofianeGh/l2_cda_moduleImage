#ifndef _CALCUL_H
#define _CALCUL_H

/** Renvoie le r�sultat de la somme de a et de b */
int intAdd(const int a, const int b);

/** Calcule a*b et renvoie le r�sultat */
int intMul(const int a, const int b);

/** Calcule a/b et renvoie le r�sultat
	@remark b!=0 sinon erreur
*/
int intDiv(const int a, const int b);

/** Calcule le factoriel de nombre
	@remark n>=0
*/
int intFactoriel(const int n);

#endif
