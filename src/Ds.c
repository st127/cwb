/*
	cwb
	File:/src/Ds.c
	Date:2021.07.10
	By MIT License.
	Copyright(C) 2021 cwb developers.All rights reserved.
*/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdarg.h>

#include"Ds.h"

#include"Ds_HashTable.c"

typedef struct {
	void *realDs;
	Cwb_Ds_Type type;
}Ds;

typedef struct {
	void *(*new)(va_list argList);
	void (*destroy)(void *ds);
	Cwb_Ds_Pair *(*search)(void *ds,va_list argList);
	Cwb_Ds_Pair *(*insert)(void *ds,va_list);
	int (*set)(void *ds,Cwb_Ds_Pair *pair,void *data);
	void *(*get)(void *ds,Cwb_Ds_Pair *pair);
	int (*delete)(void *ds,Cwb_Ds_Pair *pair);
}Ds_Prototype;

static const Ds_Prototype prototype[]={
					[CWB_DS_HASHTABLE] = {
						.new	= hashtable_new,
						.destroy= hashtable_destroy,
						.search = hashtable_search,
						.insert = hashtable_insert,
						.set	= hashtable_set,
						.get	= hashtable_get,
						.delete = hashtable_delete
					}
				      };

#define DS_PROTOTYPE(t) (prototype[(t)])

Cwb_Ds *cwb_ds_new(Cwb_Ds_Type type,...)
{
	va_list argList;
	va_start(argList,type);

	Ds *ds=(Ds*)malloc(sizeof(Ds));
	if(!ds) {
		return NULL;
	}

	ds->type=type;

	ds->realDs=DS_PROTOTYPE(type).new(argList);
	va_end(argList);
	if(!(ds->realDs)) {
		free(ds);
		return NULL;
	}

	return (Cwb_Ds*)ds;
}

void cwb_ds_destroy(Cwb_Ds *in)
{
	Ds *ds = (Ds*)in;
	DS_PROTOTYPE(ds->type).destroy(ds->realDs);
	return;
}

Cwb_Ds_Pair *cwb_ds_search(Cwb_Ds *in,...)
{
	va_list argList;
	va_start(argList,in);
	Ds *ds = (Ds*)in;

	Cwb_Ds_Pair *pair = DS_PROTOTYPE(ds->type).search(ds->realDs,argList);
	va_end(argList);

	return pair;
}

int cwb_ds_set(Cwb_Ds *in,Cwb_Ds_Pair *pair,void *data)
{
	Ds *ds = (Ds*)in;
	
	int ret = DS_PROTOTYPE(ds->type).set(ds->realDs,pair,data);
	return ret;
}

void *cwb_ds_get(Cwb_Ds *in,Cwb_Ds_Pair *pair)
{
	Ds *ds = (Ds*)in;

	void *value = DS_PROTOTYPE(ds->type).get(ds->realDs,pair);

	return value;
}

int cwb_ds_delete(Cwb_Ds *in,Cwb_Ds_Pair *pair)
{
	Ds *ds = (Ds*)in;

	return DS_PROTOTYPE(ds->type).delete(ds->realDs,pair);
}

Cwb_Ds_Pair *cwb_ds_insert(Cwb_Ds *in,...)
{
	Ds *ds = (Ds*)in;

	va_list argList;
	va_start(argList,in);

	Cwb_Ds_Pair *pair = DS_PROTOTYPE(ds->type).insert(ds->realDs,argList);
	
	va_end(argList);

	return pair;
}
