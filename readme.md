# purpose

example for including <python.h> and linking python3.lib

afterwards using pyObject* to traverse a list and find integer in list in the most unsafe manner possible

# prerequired

installed python3.xx

Environment-Variable "PYHTON3" containing basepath of your python-installation

ReleaseBuild will create searcherino.pyd next to the suche1.py

Afterwards suche1 will run timeit on increasing array-sizes using all 4 search-methods
( python -m suche1 )

drawback: currently only able to process integer-filled lists, no typechecking in cpp
