#include "udelay.h"
//fournit un delais en us pour une horloge a 64MHz
void udelay(float d)
{
  unsigned long u=64*d/3;//fhorloge*10^-6*delais(en us)/nmbr instruction boucle increment
  while(u!=0)
  {
    u--;
  }
}
