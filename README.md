# gll
Another C library usable for creation and management of generic linked lists.

## Installation and usage
Once downloaded you have to compile it, so:
1. open a shell (like the _bash_)
2. enter in the directory just downloaded (`cd /path_to_gll/gll`)
3. compile the sources (`make install`)
4. optional: test the library (`make test`) and report any issue ;)

If you want to __remove__ the binaries generated just do `make clean`.

Now, if you want to use it in your projects copy the library (_gll.o_) in the _/lib_ folder and move it where you need.
Remember to link it when you compile your programs! For example if you want to use it in your _/foo.c_ program you have to tell _gcc_ where it can find the library:
```gcc foo.c -o executable -L /path_to_gll_library -lgll```
__n.b__ For now there is no possibility to use this library in "dynamic loading" as a shared _.so_ object, but only in default "static mode". In the next versions
I'll try to add this feature.

## Api
Here you can find a short description of the functions this library offers and their signatures

#### list
Create a brand new list.
`list_t* list (int(*comp)(void*,void*), void(*mdea)(void*));`

__arguments:__
* comp : pointer to an user defined integer function used to compare two elements
* mdea : pointer to an user defined void function used to deallocate an element

__returns__ the pointer to the newly created (empty) list, __on error__ returns _NULL_ and sets _errno_ to:
* _EINVAL_ if one of the argumens is _NULL_
* _ENOMEM_ if memory errors occour

In order to use this function properly you have first to define a structure that contains the data you want to use, for example:
`
typedef struct _item {

    /*here goes your data fields*/
    
} item;
`
Then you have to provide a function to compare two different items and one to deallocate your items from the heap, here are two examples:

`
int compare (void *itm1, void *itm2) {
    int i1 = itm1-> field1;
    int i2 = itm2-> field1;
    /* do your comparing stuff here */
    return result;
}
`

`
int memory_deallocation (void *itm) {
    item* it = (item*) itm;
    /*free eventually heap allocated fields*/
    free(it);
}
`

### length
Returns the length of a list.

Currently under construction! Stay tuned!
