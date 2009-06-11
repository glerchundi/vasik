#if !defined(SWIGLUA)
typedef void *(*swig_converter_func)(void *, int *);
typedef struct swig_type_info *(*swig_dycast_func)(void **);

/* Structure to store information on one type */
typedef struct swig_type_info {
  const char             *name;         /* mangled name of this type */
  const char             *str;          /* human readable name of this type */
  swig_dycast_func        dcast;        /* dynamic cast function down a hierarchy */
  struct swig_cast_info  *cast;         /* linked list of types that can cast into this type */
  void                   *clientdata;       /* language specific type data */
  int                    owndata;       /* flag if the structure owns the clientdata */
} swig_type_info;

/* Structure to store a type and conversion function used for casting */
typedef struct swig_cast_info {
  swig_type_info         *type;         /* pointer to type that is equivalent to this type */
  swig_converter_func     converter;        /* function to cast the void pointers */
  struct swig_cast_info  *next;         /* pointer to next cast in linked list */
  struct swig_cast_info  *prev;         /* pointer to the previous cast */
} swig_cast_info;

/* this is the struct for wrappering all pointers in SwigLua
*/
typedef struct {
  swig_type_info   *type;
  int     own;  /* 1 if owned & must be destroyed */
  void        *ptr;
} swig_lua_userdata;
#endif
