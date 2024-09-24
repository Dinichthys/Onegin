#ifndef QSORT_H
#define QSORT_H

void my_qsort (void *const base, const size_t nmemb, const size_t size,
               int(*compare)(const void *, const void *));

#endif // QSORT_H
