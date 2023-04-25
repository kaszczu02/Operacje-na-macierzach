#include "matrix_utils.h"
#include "tested_declarations.h"
#include "rdebug.h"

int matrix_create(struct matrix_t *m, int width, int height) {
  if (m == NULL || width <= 0 || height <= 0) {
    return 1;
  }
  m->ptr = malloc(height * sizeof(int *));
  if (m->ptr == NULL) {
    return 2;
  }

  for (int i = 0; i < height; i++) {
    *(m->ptr + i) = (int *)calloc(width, sizeof(int));
    if (*(m->ptr + i) == NULL) {
      for (int j = 0; j < i; j++) {
        free(*(m->ptr + j));
      }
      free(m->ptr);
      return 2;
    }
  }
  m->width = width;
  m->height = height;
  return 0;
}

int matrix_read(struct matrix_t *m) {
  if (m == NULL || m->ptr == NULL || m->width <= 0 || m->height <= 0) {
    return 1;
  }

  for (int i = 0; i < m->height; i++) {
    for (int j = 0; j < m->width; j++) {
      if (scanf("%d", *(m->ptr + i) + j) != 1) {
        return 2;
      }
    }
  }
  return 0;
}

void matrix_display(const struct matrix_t *m) {
  if (m == NULL || m->ptr == NULL || m->width <= 0 || m->height <= 0) {
    return;
  }

  for (int i = 0; i < m->height; i++) {
    for (int j = 0; j < m->width; j++) {
      printf("%d ", *(*(m->ptr + i) + j));
    }
    printf("\n");
  }
}
void matrix_destroy(struct matrix_t *m) {
  if (m == NULL || m->ptr == NULL || m->width <= 0 || m->height <= 0) {
    return;
  }
  for (int i = 0; i < m->height; i++) {
    free(*(m->ptr + i));
  }
  free(m->ptr);
  m->ptr = NULL;
}

struct matrix_t *matrix_create_struct(int width, int height) {
  struct matrix_t *matrix;
  if (width <= 0 || height <= 0) {
    return NULL;
  }
  matrix = (struct matrix_t *)malloc(sizeof(struct matrix_t));
  if (matrix == NULL) {
    return NULL;
  }

  if (matrix_create(matrix, width, height) == 2) {
    free(matrix);
    return NULL;
  }

  return matrix;
}

void matrix_destroy_struct(struct matrix_t **m) {
  if (m == NULL) {
    return;
  }
  matrix_destroy(*m);
  free(*m);
  *m = NULL;
}

struct matrix_t *matrix_transpose(const struct matrix_t *m) {
  struct matrix_t *transponowana;
  if (m == NULL || m->ptr == NULL || m->width <= 0 || m->height <= 0) {
    return NULL;
  }

  transponowana = matrix_create_struct(m->height, m->width);
  if (transponowana == NULL) {
    return NULL;
  }

  for (int i = 0; i < m->height; i++) {
    for (int j = 0; j < m->width; j++) {
      *(*(transponowana->ptr + j) + i) = *(*(m->ptr + i) + j);
    }
  }
  return transponowana;
}

int matrix_save_b(const struct matrix_t *m, const char *filename) {
 
   if(filename==NULL || m==NULL || m->ptr==NULL || m->height<1 || m->width<1)
   {
     return 1;
   }

    FILE* file;
    file = fopen(filename, "wb");
    if(file ==NULL)
    {
      return 2;
    }
       
    fwrite(&m->width, sizeof(int), 1, file);
    fwrite(&m->height, sizeof(int), 1, file);
    
  for(int i=0; i<m->height; i++)
    {
      for(int j=0; j<m->width; j++)
        {
          fwrite(*(m->ptr+i)+j, sizeof(int), 1, file);
        }
            
    }
        
    fclose(file);
    return 0;
}

int matrix_save_t(const struct matrix_t *m, const char *filename) {
  FILE *file;
  if (m == NULL || m->ptr == NULL || m->width <= 0 || m->height <= 0 ||
      filename == NULL) {
    return 1;
  }
  if ((file = fopen(filename, "wt")) == NULL) {
    return 2;
  }
  fprintf(file, "%d ", m->width);

  fprintf(file, "%d\n", m->height);

  for (int i = 0; i < m->height; i++) {
    for (int j = 0; j < m->width; j++) {
      fprintf(file, "%d ", *(*(m->ptr + i) + j));
    }
    fprintf(file, "\n");
  }
  fclose(file);
  return 0;
}

struct matrix_t* matrix_copy(const struct matrix_t *m)
{
    if(m==NULL || m->ptr==NULL || m->width<=0 || m->height<=0 )
    {
        return NULL;
    }

    struct matrix_t *macierz;

    macierz=matrix_create_struct(m->width,m->height);
    if(macierz==NULL)
    {
        return NULL;
    }

    for(int i=0;i<m->height;i++)
    {
        for(int j=0;j<m->width;j++)
        {
            *(*(macierz->ptr+i)+j)=*(*(m->ptr+i)+j);
        }
    }

    return macierz;
}

struct matrix_t* matrix_add(const struct matrix_t *m1, const struct matrix_t *m2)
{
    if(m1==NULL || m2==NULL || m1->ptr==NULL || m2->ptr==NULL || m1->width<=0 || m2->width<=0 || m1->height<=0 || m2->height<=0 || m1->width!=m2->width || m1->height!=m2->height)
    {
        return NULL;
    }
    struct matrix_t *w;
    w=matrix_create_struct(m1->width,m1->height);
    if(w==NULL)
    {
        return NULL;
    }

    for(int i=0;i<m1->height;i++)
    {
        for(int j=0;j<m1->width;j++)
        {
            *(*(w->ptr+i)+j)=*(*(m1->ptr+i)+j) + *(*(m2->ptr+i)+j);
        }
    }

    return w;
}

struct matrix_t* matrix_subtract(const struct matrix_t *m1, const struct matrix_t *m2)
{
    if(m1==NULL || m2==NULL || m1->ptr==NULL || m2->ptr==NULL || m1->width<=0 || m2->width<=0 || m1->height<=0 || m2->height<=0 || m1->width!=m2->width || m1->height!=m2->height)
    {
        return NULL;
    }
    struct matrix_t *w;
    w=matrix_create_struct(m1->width,m1->height);
    if(w==NULL)
    {
        return NULL;
    }

    for(int i=0;i<m1->height;i++)
    {
        for(int j=0;j<m1->width;j++)
        {
            *(*(w->ptr+i)+j)=*(*(m1->ptr+i)+j)-*(*(m2->ptr+i)+j);
        }
    }

    return w;
}

struct matrix_t* matrix_multiply(const struct matrix_t *m1, const struct matrix_t *m2)
{
    if(m1==NULL || m2==NULL || m1->ptr==NULL || m2->ptr==NULL || m1->width<=0 || m2->width<=0 || m1->height<=0 || m2->height<=0 || m1->width!=m2->height)
    {
        return NULL;
    }
    struct matrix_t *w;
    w=matrix_create_struct(m2->width,m1->height);
    if(w==NULL)
    {
        return NULL;
    }

    for(int i=0;i<m1->height;i++)
    {
        for(int j=0;j<m2->width;j++)
        {
            *(*(w->ptr+i)+j)= 0;
            for(int k=0;k<m1->width;k++)
            {
                *(*(w->ptr+i)+j)+=*(*(m1->ptr+i)+k) * *(*(m2->ptr+k)+j);
            }
        }
    }

    return w;
}
struct matrix_t* matrix_load_b(const char *filename, int *err_code)
{
    FILE *file;
    int width,height;
    if(filename==NULL)
    {
        if(err_code!=NULL)
        {
            *err_code=1;
        }
        return NULL;
    }
    if((file=fopen(filename,"rb"))==NULL)
    {
        if(err_code!=NULL)
        {
            *err_code=2;
        }
        return NULL;
    }
    if(fread(&width,sizeof(width),1,file)!=1)
    {
        if(err_code!=NULL)
        {
            *err_code=3;
        }
        fclose(file);
        return NULL;
    }
    if(fread(&height,sizeof(height),1,file)!=1)
    {
        if(err_code!=NULL)
        {
            *err_code=3;
        }
        fclose(file);
        return NULL;
    }

    if(height<=0 || width<=0)
    {
        if(err_code!=NULL)
        {
            *err_code=3;
        }
        fclose(file);
        return NULL;
    }

    struct matrix_t *w;
    w=matrix_create_struct(width,height);
    if(w==NULL)
    {
        if(err_code!=NULL)
        {
            *err_code=4;
        }
        fclose(file);
        return NULL;
    }

    for(int i=0;i<height;i++)
    {
        for(int j=0;j<width;j++)
        {
            if(fread(*(w->ptr+i)+j,sizeof(*(*(w->ptr+i)+j)),1,file)<1)
            {
                if(err_code!=NULL)
                {
                    *err_code=3;
                }
                matrix_destroy_struct(&w);
                fclose(file);
                return NULL;
            }
        }
    }

    fclose(file);
    if(err_code!=NULL)
    {
        *err_code=0;
    }
    return w;
}

struct matrix_t* matrix_load_t(const char *filename, int *err_code)
{
    FILE *file;
    int width,height;
    if(filename==NULL)
    {
        if(err_code!=NULL)
        {
            *err_code=1;
        }
        return NULL;
    }
    if((file=fopen(filename,"rt"))==NULL)
    {
        if(err_code!=NULL)
        {
            *err_code=2;
        }
        return NULL;
    }
    if(fscanf(file,"%d",&width)!=1)
    {
        if(err_code!=NULL)
        {
            *err_code=3;
        }
        fclose(file);
        return NULL;
    }
    if(fscanf(file,"%d",&height)!=1)
    {
        if(err_code!=NULL)
        {
            *err_code=3;
        }
        fclose(file);
        return NULL;
    }

    if(height<=0 || width<=0)
    {
        if(err_code!=NULL)
        {
            *err_code=3;
        }
        fclose(file);
        return NULL;
    }

    struct matrix_t *w;
    w=matrix_create_struct(width,height);
    if(w==NULL)
    {
        if(err_code!=NULL)
        {
            *err_code=4;
        }
        fclose(file);
        return NULL;
    }

    for(int i=0;i<height;i++)
    {
        for(int j=0;j<width;j++)
        {
            if(fscanf(file,"%d",*(w->ptr+i)+j)!=1)
            {
                if(err_code!=NULL)
                {
                    *err_code=3;
                }
                matrix_destroy_struct(&w);
                fclose(file);
                return NULL;
            }
        }
    }
    fclose(file);
    if(err_code!=NULL)
    {
        *err_code=0;
    }
    return w;
}

