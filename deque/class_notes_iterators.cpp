// class notes for the list iterator
iterator list :: begin()
{
    return iterator(pHead);
}

iterator list :: end()
{
    return iterator(NULL);
}

iterator & iterator ++ ()
{
    if (pNext != NULL)
        p = p->pNext;
    return *this;
}

T & iterator :: operator * ()
{
    return p->data;
}
