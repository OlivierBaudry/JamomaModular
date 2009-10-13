/*
 * jcom.snapshot
 * External for Jamoma: capture, recall, transform, and manipulate global snapshots
 * By Timothy Place, Copyright 2009
 *
 * License: This code is licensed under the terms of the GNU LGPL
 * http://www.gnu.org/licenses/lgpl.html
 */

#include "Jamoma.h"

class SnapshotParameterValue {
public:
    TTFloat64   value;
    ObjectPtr   parameter;

    SnapshotParameterValue(TTFloat64& f, ObjectPtr o):
        value(f),
        parameter(o)
    {;}


};

// A vector of 64-bit floats used to represent a given snapshot
typedef vector<SnapshotParameterValue>  Snapshot;
typedef Snapshot::iterator              SnapshotIter;
typedef Snapshot*                       SnapshotPtr;

// A vector (or collection) of snapshots
typedef vector<SnapshotPtr>             SnapshotCollection;
typedef SnapshotCollection::iterator    SnapshotCollectionIter;
typedef SnapshotCollection*             SnapshotCollectionPtr;

// Data Structure for this object
typedef struct {
    Object                  ob;
    TTTreePtr               tree;
    SnapshotCollectionPtr   snapshots;
} TTModSnapshot;
typedef TTModSnapshot* TTModSnapshotPtr;


// Prototypes
TTPtr       TTModSnapshotNew    (SymbolPtr name, AtomCount argc, AtomPtr argv);
void        TTModSnapshotFree   (TTModSnapshotPtr self);
MaxErr      TTModSnapshotNotify (TTModSnapshotPtr self, SymbolPtr s, SymbolPtr msg, void *sender, void *data);
void        TTModSnapshotAssist (TTModSnapshotPtr self, void *b, long m, long a, char *s);
void        TTModSnapshotDump   (TTModSnapshotPtr self);
void        TTModSnapshotStore  (TTModSnapshotPtr self, SymbolPtr s, AtomCount argc, AtomPtr argv);
void        TTModSnapshotRecall (TTModSnapshotPtr self, SymbolPtr s, AtomCount argc, AtomPtr argv);


// Shared
static ClassPtr sMaxClass;


// Class Definition
int JAMOMA_EXPORT_MAXOBJ main(void)
{
    ClassPtr c = class_new("jcom.snapshot",
                           (method)TTModSnapshotNew,
                           (method)TTModSnapshotFree,
                            sizeof(TTModSnapshot),
                            NULL, A_GIMME, 0);

    jamoma_init();
    common_symbols_init();

    class_addmethod(c, (method)TTModSnapshotNotify,     "notify",       A_CANT, 0);
    class_addmethod(c, (method)TTModSnapshotAssist,     "assist",       A_CANT, 0);
    class_addmethod(c, (method)TTModSnapshotDump,       "dump",         0);
    class_addmethod(c, (method)TTModSnapshotStore,      "store",        A_GIMME, 0);
    class_addmethod(c, (method)TTModSnapshotRecall,     "recall",       A_GIMME, 0);

    class_register(_sym_box, c);
    sMaxClass = c;
    return 0;
}


#if 0
#pragma mark -
#pragma mark Life Cycle
#endif 0

TTPtr TTModSnapshotNew(SymbolPtr name, AtomCount argc, AtomPtr argv)
{
    TTModSnapshotPtr self = (TTModSnapshotPtr)object_alloc(sMaxClass);

    if (self) {
        self->snapshots = new SnapshotCollection;
        self->tree = jamoma_tree_init();
    }
    return self;
}

void TTModSnapshotFree(TTModSnapshotPtr self)
{
    // TODO: leaking memory! -- free of the actuall snapshots held by the pointers!
    delete self->snapshots;
}


#if 0
#pragma mark -
#pragma mark Methods
#endif 0

MaxErr TTModSnapshotNotify(TTModSnapshotPtr self, SymbolPtr s, SymbolPtr msg, TTPtr sender, TTPtr data)
{
    object_post(SELF, "notification : %s", msg->s_name);
    return MAX_ERR_NONE;
}


void TTModSnapshotAssist(TTModSnapshotPtr self, void* b, long msg, long arg, char* dst)
{
    if (msg == ASSIST_INLET) {  // inlet
        if (arg == 0)
            strcpy(dst, "inlet");
    }
    else {                      // outlet
        if (arg == 0)
            strcpy(dst, "outlet");
    }
}


void TTModSnapshotDump(TTModSnapshotPtr self)
{
    jamoma_tree_dump(); // dump all the address of the tree in the Max window
}


void TTModSnapshotStore(TTModSnapshotPtr self, SymbolPtr s, AtomCount argc, AtomPtr argv)
{
    TTNodePtr   rootNode = self->tree->getRoot();
    TTValue     moduleNodes;
    TTUInt32    numModules;
    TTListPtr   returnedChildren = NULL;
    TTErr       err;
    SnapshotPtr snapshot = NULL;
    TTUInt32    snapshotIndex = 0;

    if (argc && argv)
        snapshotIndex = atom_getlong(argv);

    if (snapshotIndex >= self->snapshots->size()) {
        if (snapshotIndex >= self->snapshots->capacity()) {
            self->snapshots->reserve(snapshotIndex+1);
        }
        self->snapshots->resize(snapshotIndex+1);
    }
    else {
        snapshot = self->snapshots->at(snapshotIndex);
        delete snapshot;
        snapshot = NULL;
    }
    snapshot = new Snapshot;


    err = rootNode->getChildren(TT("*"), TT("*"), &returnedChildren);

    returnedChildren->assignToValue(moduleNodes);
    numModules = moduleNodes.getSize();
    for (TTUInt32 i=0; i<numModules; i++) {
        TTNodePtr   module = NULL;
        TTSymbolPtr type;

        moduleNodes.get(i, (TTPtr*)(&module));
        if (module) {
            type = module->getType();
            if (type == TT("hub")) {
                TTValue     parameterNodes;
                TTUInt32    numParameters;

                post("  Module: %s", module->getName()->getCString());
                err = module->getChildren(TT("*"), TT("*"), &returnedChildren);
                returnedChildren->assignToValue(parameterNodes);
                numParameters = parameterNodes.getSize();
                for (TTUInt32 i=0; i<numParameters; i++) {
                    TTNodePtr   parameter = NULL;
                    TTSymbolPtr childType;

                    parameterNodes.get(i, (TTPtr*)(&parameter));
                    if (parameter) {
                        childType = parameter->getType();
                        if (childType == TT("subscribe_parameter")) {   // FIXME: this name sucks for the type.
                            ObjectPtr maxObject = (ObjectPtr)parameter->getObject();
                            SymbolPtr maxType = object_attr_getsym(maxObject, SymbolGen("type"));

                            if (maxType == SymbolGen("decimal") || maxType == SymbolGen("integer")) {
                                TTFloat64               value = object_attr_getfloat(maxObject, SymbolGen("value"));
                                SnapshotParameterValue  spv(value, maxObject);

                                snapshot->push_back(spv);
                                post("    parameter: %s -- value: %lf", parameter->getName()->getCString(), value);

                            }
                        }
                    }
                }
            }
        }
    }
//    ((*self->snapshots)[snapshotIndex]).reserve(snapshot.size()+1);
  (*self->snapshots)[snapshotIndex] = snapshot;

//  ((*self->snapshots)[snapshotIndex]).assign(snapshot.begin(), snapshot.end());

//  ((*self->snapshots)[snapshotIndex]).clear();
//  ((*self->snapshots)[snapshotIndex]).insert(((*self->snapshots)[snapshotIndex]).begin(), snapshot.begin(), snapshot.end());
}


void TTModSnapshotRecallOne(const SnapshotParameterValue& spv)
{
    //object_attr_setfloat(spv.parameter, _sym_value, spv.value);
    object_method(spv.parameter, _sym_float, spv.value);
}

void TTModSnapshotRecall(TTModSnapshotPtr self, SymbolPtr s, AtomCount argc, AtomPtr argv)
{
    if (!argc || !argv)
        return;

    if (argc == 1) {
        SnapshotPtr snapshot;
        TTUInt32    snapshotIndex = atom_getlong(argv);

        if (snapshotIndex >= self->snapshots->size()) {
            object_error(SELF, "preset recall out of range");
            return;
        }
        snapshot = (*self->snapshots)[snapshotIndex];
        for_each((*snapshot).begin(), (*snapshot).end(), TTModSnapshotRecallOne);
    }
    else if (argc == 3) {
        SnapshotPtr snapshotA;
        SnapshotPtr snapshotB;
        TTUInt32    snapshotIndexA = atom_getlong(argv+0);
        TTUInt32    snapshotIndexB = atom_getlong(argv+1);
        TTUInt32    snapshotSizeA = atom_getlong(argv+0);
        TTUInt32    snapshotSizeB = atom_getlong(argv+1);
        TTFloat32   position = atom_getfloat(argv+2);

        if (snapshotIndexA >= self->snapshots->size() ||
            snapshotIndexB >= self->snapshots->size())
        {
            object_error(SELF, "preset recall out of range");
            return;
        }

        snapshotA = (*self->snapshots)[snapshotIndexA];
        snapshotB = (*self->snapshots)[snapshotIndexB];
        snapshotSizeA = snapshotA->size();
        snapshotSizeB = snapshotB->size();

        if (snapshotSizeA != snapshotSizeB) {
            object_error(SELF, "preset recall -- cannot interpolate between snapshots of unequal size");
            return;
        }

        for (TTUInt32 i=0; i<snapshotSizeA; i++) {
            if ( (*snapshotA)[i].parameter == (*snapshotB)[i].parameter ) {
                TTFloat32 f = ((*snapshotA)[i].value * (1.0 - position)) + ((*snapshotB)[i].value * (position));
                object_method((*snapshotA)[i].parameter, _sym_float, f);
            }
        }
    }
}

