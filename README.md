# gll
Another C library usable for creation and management of generic linked lists.

# Installation and usage
Once downloaded you have to compile it, so:
* open a shell (like the _bash_)
* enter in the directory just downloaded (`cd /path_to_gll/gll`)
* compile the sources (`make install`)
* optional: test the library (`make test`) and report any issue ;)

If you want to __remove__ the binaries generated just do `make clean`.

Now, if you want to use it in your projects copy the library (_gll.o_) in the _/lib_ folder and move it where you need.
Remember to link it when you compile your programs!
For example: if you want to use it in your _/foo.c_ program you have to tell _gcc_ where it can find the library:
`gcc foo.c -o executable -L /path_to_gll_library -lgll`

__n.b__ For now there is no possibility to use this library in "dynamic loading" as a shared _.so_ object,
but only in default "static mode". In the next versions I'll try to add this feature.

__n.b.__ Indexes starts from 0.

# Api
Here you can find a short description of the functions this library offers and their signatures

##list
Create a brand new list.
`list_t* list (int(*comp)(void*,void*), void(*mdea)(void*));`

__arguments:__
* comp: pointer to an user defined integer function used to compare two elements
* mdea: pointer to an user defined void function used to deallocate an element

__returns__ the pointer to the newly created (empty) list, __on error__ returns _NULL_ and sets _errno_ to:
* _EINVAL_ if one of the argumens is null
* _ENOMEM_ if memory errors occour

In order to use this function properly you have first to define a structure that contains the data you want to use,
for example:
```
typedef struct _item {

    /*here goes your data fields*/

} item;
```
Then you have to provide a function to compare two different items and one to deallocate your items from the heap, here are two examples:

```
int compare (void *itm1, void *itm2) {
    int i1 = itm1-> field1;
    int i2 = itm2-> field1;
    /* do your comparing stuff here */
    return result;
}
```

```
int memory_deallocation (void *itm) {
    item* it = (item*) itm;
    /*free eventually heap allocated fields*/
    free(it);
}
```

## length
Return the length of a list.
`int length (list_t* list);`

__arguments:__
* list: pointer to the list

__returns__ the length of the list, __on error__ returns _-1_ and sets _errno_ to _EINVAL_ if the argument is null

## push
Insert an element in the head of a list.
`int push (list_t* list, void* data, int size);`

__arguments:__
* list: pointer to the list
* data: pointer to the element
* size: size of the element

__returns__ _0_ if the function ends correctly, __on error__  returns _1_ and sets _errno_ to:
* _ENOMEM_ if memory error occours
* _EINVAL_ if one of the arguments is null or zero

## append
Append an element to the tail of a list.
`int append (list_t* list, void* data, int size);`

__arguments:__
* list: pointer to the list
* data: pointer to the element
* size: size of the element

__returns__ _0_ if the function terminates correctly, __on error__  returns _1_ and sets _errno_ to:
* _ENOMEM_ if memory error occours
* _EINVAL_ if one of the arguments is null or zero

## pop
Return and remove the first element of a list.
`void* pop (list_t*);`

__arguments:__
* list: pointer to the list

__returns__ the pointer to the first element of the list, __on error__ returns _NULL_ and sets _errno_ to:
* _ENODATA_ if the list is empty
* _EINVAL_ if the argument is null

## cut
Return and remove the tail of a list.
`void* cut (list_t* list);`

__arguments:__
* list: pointer to the list

__returns__ the pointer to the tail of the list, __on error__ returns _NULL_ and sets _errno_ to:
* _ENODATA_ if the list is empty
* _EINVAL_ if the argument is null

## remove_element
Remove an element at the specified position from a list.
`int remove_element (list_t* list, int pos);`

__arguments:__
* list: pointer to the list
* pos: position of the element

__returns__ _0_ if the function ends correctly, __on error__ returns _1_ and sets _errno_ to:
* _EINVAL_ if one of the arguments is null or if _pos_ < 0 or _pos_ >= length(list)
* _ENODATA_ if the list is empty

## get
Returns a copy of the element at the specified position.
`void* get (list_t* list, int pos);`

__arguments:__
* list: pointer to the list
* pos: position of the element

__returns__ the pointer to a copy of the element, __on error__ returns _NULL_ and sets _errno_ to:
* _EINVAL_ if one of the arguments is null or if _pos_ < 0 or _pos_ >= length(list)
* _ENODATA_ if the list is empty
* _ENOMEM_ if memory error occours

## set
Set the element at the specified position.
`int set (list_t* list, void* data, int pos);`

__arguments:__
* list: pointer to the list
* data: pointer to the new element
* pos: position of the element

__returns__ _0_ if the function ends correctly, __on error__ returns _1_ and sets _errno_ to:
* _EINVAL_ if one of the arguments is null or if _pos_ < 0 or _pos_ >= length(list)
* _ENODATA_ if the list is empty

## index_of
Return the position of the first occourrence of an element.
`int index_of (list_t* list, void* data);`

__arguments:__
* list: pointer to the list
* data: pointer to the elements

__returns__ the index of the element (count start from 0), __on error__ returns _-1_ and sets _errno_ to:
* _ENODATA_ if the list is empty
* _EINVAL_ if one of the arguments is null

__n.b.__ this function performs a _deep test_ so it will compare the data, not the pointers.

## destroy
Destroy a list and all its elements.
`void destroy (list_t* list);`

__arguments:__
* list: pointer to the list

__returns:__ void, __errors are not checked__ like null arguments or errors while freeing memory

## map
Return a new list where its elements are the result of an user provided function applied to all the elements of another list.
`list_t* map (list_t* list, void*(*fun)(void*));`

__arguments:__
* list: pointer to the list
* fun: pointer to the function

__returns:__ the pointer fo the newly "mapped" list, __on error__ returns _NULL_ and sets _errno_ to:
* _EINVAL_ if one of the arguments is null
* _ENODATA_ if the list is empty

In order to use this function you have to provide a special function that performs the requested operation on the elements: it have to
takes an item, select the field, performs an operation on the data and return a new item with the data processed.
For example: if you have an "int list" with your elements structured like this:
```
typedef struct _item {
  int value;
} item;
```
...and you want to make a new list where all its elements have the same values of another list plus 10, then you have to define a
function like this one:
```
void* plus10 (void* itm) {
  item* i = (item*) itm;
  item* new_i = (item*) malloc(sizeof(item));
  /* error check ... */
  new_i->value = i->value + 10;
  return new_i;
}
```

## filter
Return a new list where its elements are the result of "filtering" another list using a function provided by the user.
`list_t* filter (list_t*, int(*fun)(void*));`

__arguments:__
* list: pointer to the list
* fun: pointer to the function

__returns:__ the pointer fo the newly "filtered" list, __on error__ returns _NULL_ and sets _errno_ to:
* _EINVAL_ if one of the arguments is null
* _ENODATA_ if the list is empty

In order to use this function you have to provide a special function that takes an item, examinates a field and choose if mantain that
element or not.
For example: if you have an "int list" with your elements structured like in the example above and you want to make a new list where
all its elements are only the odd elements contained into another list, then you have to define a function like this one:
```
int isOdd (void* itm) {
  item* i = (item*) itm;
  /* error check ... */
  return i->value % 2 != 0;
}
```
Currently under construction! Stay tuned!
