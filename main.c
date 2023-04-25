#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "matrix_utils.h"
#include "tested_declarations.h"
#include "rdebug.h"

int main() 
{
  char *tab;
  int err_code = 0;
  struct matrix_t *macierz;
  struct matrix_t *macierz2;
  
  tab = (char*)malloc(20 * sizeof(char));
  if(tab==NULL)
  {
    printf("Failed to allocate memory");
    return 8;
  }

  //wczytywanie do pierwszej macierzy
  printf("Podaj sciezke do pliku:\n");
  scanf("%19[^\n]", tab);

  
  if (strchr(tab, '.') == NULL)
  {
    printf("Unsupported file format");
    free(tab);
    return 7;
  }
  if (strcmp(strchr(tab, '.'), ".txt") == 0)
  {
    macierz = matrix_load_t(tab,&err_code);

    if(err_code == 4 && macierz == NULL)
    {
        printf("Failed to allocate memory");
        free(tab);
        return 8;
    }
    else if(err_code == 3 )
      {
          printf("File corrupted");
          free(tab);
          return 6;
      }
    else if (macierz == NULL && err_code == 2)
    {
      printf("Couldn't open file");
      free(tab);
      return 4;
    }

  }
  else if (strcmp(strchr(tab, '.'), ".bin") == 0)
  {
    macierz = matrix_load_b(tab,&err_code);

      if(err_code == 4 && macierz == NULL)
      {
          printf("Failed to allocate memory");
          free(tab);
          return 8;
      }
      else if(err_code == 3 )
      {
          printf("File corrupted");
          free(tab);
          return 6;
      }
      else if (macierz == NULL && err_code == 2)
      {
        printf("Couldn't open file");
        free(tab);
        return 4;
    }

  }
  else
  {
    printf("Unsupported file format");
    free(tab);
    return 7;
  }

    while(getchar()!='\n');

    //wczytywanie do drugiej macierzy
  printf("Podaj sciezke do pliku:\n");
  scanf("%19[^\n]", tab);


  if (strchr(tab, '.') == NULL)
  {
    printf("Unsupported file format");
    matrix_destroy_struct(&macierz);
    free(tab);
    return 7;
  }

  if (strcmp(strchr(tab, '.'), ".txt") == 0)
  {
    macierz2 = matrix_load_t(tab, &err_code);

    if(macierz2 == NULL && err_code == 4)
    {
        printf("Failed to allocate memory");
        matrix_destroy_struct(&macierz);
        free(tab);
        return 8;
    }
    else if(err_code == 3 )
      {
          printf("File corrupted");
          matrix_destroy_struct(&macierz);
          free(tab);
          return 6;
      }
    else if (macierz2 == NULL && err_code == 1) {
      printf("Couldn't open file");
        matrix_destroy_struct(&macierz);
      free(tab);
      return 4;
    }

  }
  else if (strcmp(strchr(tab, '.'), ".bin") == 0)
  {
    macierz2 = matrix_load_b(tab, &err_code);

      if(macierz2 == NULL && err_code == 4)
      {
          printf("Failed to allocate memory");
          matrix_destroy_struct(&macierz);
          free(tab);
          return 8;
      }
      else if (macierz2 == NULL && err_code == 2)
      {
        printf("Couldn't open file");
        matrix_destroy_struct(&macierz);
        free(tab);
        return 4;
      }
      else if(err_code == 3 )
      {
          printf("File corrupted");
          matrix_destroy_struct(&macierz);
          free(tab);
          return 6;
      }

  }
  else
  {
    printf("Unsupported file format");
      matrix_destroy_struct(&macierz);
    free(tab);
    return 7;
  }
  free(tab);

  //dodawanie
  struct matrix_t *macierz3;
  macierz3 = matrix_add(macierz,macierz2);
  if(macierz3 == NULL)
  {
    printf("Error\n");
  }
  matrix_display(macierz3);
  matrix_destroy_struct(&macierz3);

  //odejmowanie
  macierz3 = matrix_subtract(macierz,macierz2);
  if(macierz3 == NULL)
  {
    printf("Error\n");
  }
  matrix_display(macierz3);
  matrix_destroy_struct(&macierz3);

  //mnozenie
  macierz3 = matrix_multiply(macierz,macierz2);
  if(macierz3 == NULL)
  {
    printf("Error\n");
  }
  matrix_display(macierz3);
  matrix_destroy_struct(&macierz3);

  //czyszczenie
  matrix_destroy_struct(&macierz);
  matrix_destroy_struct(&macierz2);
  matrix_destroy_struct(&macierz3);

  return 0;
}

