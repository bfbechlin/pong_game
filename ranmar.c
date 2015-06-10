/*Below is a c version of ranmar and rmarin.  Note that this version
of rmarin requires 2 integers input and does not have ntotin or ntotin2*/
/*****************************************************************
*                                                                *
*  ranmar1(ran)                                                  *
*                                                                *
*       This is the ranmar random number generator put into c    *
*       and modified to give 1 number at a time                  *
*       The version here is for the MIPs and has an _            *
*       It pops one number off a list of randoms, invoking the   *
*       random generator only if the list is empty.  It follows  *
*       the Fermilab random number generator in this.            *
*       It is set up here as a subroutine, not a function as is  *
*       ranmar.                                                  *
*       The initialization routine is called rmarin(ij,kl)       *
*       This routine must be called with 0<=ij<=31328            *
*                                        0<=kl<=30081            *
*       For the same ij a new sequence is generated for eack kl  *
*       The length of the sequence is 2**144                     *
*       See F. James CERN DD/88/22 December 1988.                *
*                                                                *
*       Byron Roe                                                *
*       University of Michigan                                   *
*       May 1, 1989                                              *
*                                                                *
******************************************************************/
#define LEN 255

static float u[97],c,cd,cm;
static int i97,j97,ileft;

void ranmar1_(float *ran)
   {
   register float uni, cint;
   register float* listptr;
   register int ivec,i97int,j97int;
   static float rvec[LEN];
   if (ileft < 0)
      {
      i97int = i97;
      j97int = j97;
      cint = c;
      for (ivec = 0; ivec <= LEN; ivec++)
         {
         uni = u[i97int] - u[j97int];
         if (uni < 0) uni++;
         u[i97int--] = uni;
         if (i97int < 0) i97int = 96;
         j97int--;
         if (j97int < 0) j97int = 96;
         cint -= cd;
         if (cint < 0.) cint += cm;
         uni -= cint;
         if ( uni < 0.) uni++;
         rvec[ivec] = uni;
         }
      ileft = LEN;
      c = cint;
      j97 = j97int;
      i97 = i97int;
      }
   *ran = rvec[ileft--];
   }
/*****************************************************************/
void rmarin_(int ij, int kl)
   {
   int i,j,k,l,m,ii,jj;
   float s,t;
   i = ((ij/177) % 177) + 2;
   j = (ij % 177) + 2;
   k = ((kl/169) % 178) + 1;
   l = kl  % 169;
   for (ii = 0; ii <= 96; ii++)
      {
      s = 0;
      t = .5;
      for (jj = 1; jj <= 24; jj++)
         {
         m = (( (i*j) % 179)*k) % 179;
         i = j;
         j = k;
         k = m;
         l = (53*l +1) % 169;
         if (( (l*m) % 64) >= 32) s = s + t;
         t = 0.5 * t;
         }
      u[ii] = s;
      }
   c = 362436./16777216.;
   cd = 7654321./16777216.;
   cm = 16777213./16777216.;
   i97 = 96;
   j97 = 32;
   ileft=(-1);
   }
/*****************************************************************/
