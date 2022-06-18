import searcherino

def suche(l: list,e:int) ->int:
    for i in range(len(l)):
        if l[i]==e:
            return i
    return -1


def suche2(l: list,e: int) ->int:
    for i,val in enumerate(l):
        if val==e:
            return i
    return -1

def binsearch(l: list,e: int) ->int:
    minIndex=0
    maxIndex=len(l)-1
    while(maxIndex>=minIndex):
        midIndex=(maxIndex+minIndex)//2
        val=l[midIndex]
        if val>e:
            maxIndex=midIndex-1
        elif val<e:
            minIndex=midIndex+1
        else:
            return midIndex
    return -1

def extsearch(l:list,e:int)->int:
    return searcherino.binsearch_cpp(l,e)

def initlist(count:int ):
    global liste
    global lastItem
    if count<0:
        liste=[]
        lastItem=-1
        return

    #liste=[0,1,2,8,13,17,19,32,42]
    import random
    liste = random.sample(range(count*2), count)
    lastItem=-1
    if len(liste)>0:
        lastItem=liste[len(liste)-1]
        liste.sort()

def test1() ->int:
    return suche(liste,lastItem)

def test2() ->int:
    return suche2(liste,lastItem)

def test3() ->int:
    return binsearch(liste,lastItem)

def test4() ->int:
    return extsearch(liste,lastItem)

if __name__ == '__main__':
    import timeit
    for c in range(17):
        cnt=(2**c)-1
        initlist(cnt)
        print(f"listsize {cnt} , searchfor {lastItem}")
        winner="test1"
        minT=timeit.timeit("test1()", number=10000,globals=globals())
        print(minT)

        t2=timeit.timeit("test2()", number=10000,globals=globals())
        print(t2)
        if t2<minT:
            minT=t2
            winner="test2"
        t3=timeit.timeit("test3()", number=10000,globals=globals())
        print(t3)
        if t3<minT:
            minT=t3
            winner="test3"

        t4=timeit.timeit("test4()", number=10000,globals=globals())
        print(t4)
        if t4<minT:
            minT=t4
            winner="test4"

        print(f"{cnt} :\t: winner is {winner} with {minT}")