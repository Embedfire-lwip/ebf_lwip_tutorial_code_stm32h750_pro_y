#include "cJSON_Process.h"
#include "main.h"
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
/*******************************************************************
 *                          ��������                               
 *******************************************************************/



cJSON* cJSON_Data_Init(void)
{
  cJSON* cJSON_Root = NULL;    //json���ڵ�
  
  cJSON_Root = cJSON_CreateObject();   /*������Ŀ*/
  if(NULL == cJSON_Root)
  {
      return NULL;
  }
  cJSON_AddStringToObject(cJSON_Root, NAME, DEFAULT_NAME);  /*���Ԫ��  ��ֵ��*/
  cJSON_AddNumberToObject(cJSON_Root, TEMP_NUM, DEFAULT_TEMP_NUM);
  cJSON_AddNumberToObject(cJSON_Root, HUM_NUM, DEFAULT_HUM_NUM);
  
  char* p = cJSON_Print(cJSON_Root);  /*p ָ����ַ�����json��ʽ��*/
  
//  PRINT_DEBUG("%s\n",p);
  
  vPortFree(p);
  p = NULL;
  
  return cJSON_Root;
  
}
uint8_t cJSON_Update(const cJSON * const object,const char * const string,void *d)
{
  cJSON* node = NULL;    //json���ڵ�
  node = cJSON_GetObjectItem(object,string);
  if(node == NULL)
    return NULL;
  if(cJSON_IsBool(node))
  {
    int *b = (int*)d;
//    printf ("d = %d",*b);
    cJSON_GetObjectItem(object,string)->type = *b ? cJSON_True : cJSON_False;
//    char* p = cJSON_Print(object);    /*p ָ����ַ�����json��ʽ��*/
    return 1;
  }
  else if(cJSON_IsString(node))
  {
    cJSON_GetObjectItem(object,string)->valuestring = (char*)d;
//    char* p = cJSON_Print(object);    /*p ָ����ַ�����json��ʽ��*/
    return 1;
  }
  else if(cJSON_IsNumber(node))
  {
    double *num = (double*)d;
//    printf ("num = %f",*num);
//    cJSON_GetObjectItem(object,string)->valueint = (double)*num;
    cJSON_GetObjectItem(object,string)->valuedouble = (double)*num;
//    char* p = cJSON_Print(object);    /*p ָ����ַ�����json��ʽ��*/
    return 1;
  }
  else
    return 1;
}

void Proscess(void* data)
{
  PRINT_DEBUG("��ʼ����JSON����");
  cJSON *root,*json_name,*json_temp_num,*json_hum_num;
  root = cJSON_Parse((char*)data); //������json��ʽ
  
  json_name = cJSON_GetObjectItem( root , NAME);  //��ȡ��ֵ����
  json_temp_num = cJSON_GetObjectItem( root , TEMP_NUM );
  json_hum_num = cJSON_GetObjectItem( root , HUM_NUM );

  PRINT_DEBUG("name:%s\n temp_num:%f\n hum_num:%f\n",
              json_name->valuestring,
              json_temp_num->valuedouble,
              json_hum_num->valuedouble);

  cJSON_Delete(root);  //�ͷ��ڴ� 
}








