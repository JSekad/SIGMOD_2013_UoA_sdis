# softDevForInfSystems2 (FINAL)

This is the Second Deliverable for "Software Development For Information Systems"
Developers:

**sdi1600148 Tsolkas Nikolaos**

**sdi1800241 Agoris Konstantinos**

**sdi1800250 Sekadakis Ioannis**

Στο πρόγραμμα έχουμε υλοποιήσει μια δομή vector.

Ορίζουμε σαν global μεταβλητές τις δομές που χρησιμοποιούμε στις βασικές συναρτήσεις οι οποίες είναι ένα hash table για την exact match, ένα bktree για την edit distance και έναν vector με 27 bktrees(4-31) για την hamming distance.

Επίσης ορίζουμε σαν global ένα vector queries το οποίο χρησιμεύει στο να κρατάμε τις πληροφορίες από κάθε query. Ένα vector documents στο οποίο αποθηκεύουμε τις πληροφορίες του document το οποίο καλείται στην match document. Τέλος, ένα vector results στο οποίο αποθηκεύουμε τα αποτελέσματα που βρίσκουμε για το κάθε document το οποίο βρίσκετε υπό επεξεργασία και έναν counter ο οποίος χρησιμεύει στην get next available results.

Στη συνάρτηση start query εισάγουμε κάθε query βάση το match type του και to match distance του στην αντίστοιχη δομή. Επίσης εισάγουμε τα στοιχεία του κάθε query στο vector που κρατάει όλα τα queries.

Στη συνάρτηση math document αρχικά αρχικοποιούμε μια entry list η οποία κρατάει προσωρινά όλα τα results που θα βρούμε σε όλες τις δομές. Αφού διατρέξουμε όλες τις δομές για κάθε λέξη του κειμένου βλέπουμε ποιες από τις λέξεις που έχουν κάνει match εκπληρώνουν τα requirements του κάθε query. Στο τέλος μένει η λίστα με τα σωστά query id.

Στην συνάρτηση get next available results κρατάμε ένα global counter ο οποίος  μας δείχνει το επόμενο διαθέσιμο αποτέλεσμα από τα αποτελέσματα που έχουμε βρει.

Στην End query αποφασίσαμε να κάνουμε soft delete και απλά αλλάζουμε ένα flag το οποίο βρίσκετε στις πληροφορίες του κάθε query από 1 σε 0.

To πρόγραμμα τρέχει με τις εντολές make gdb για debug και make valgrind για την εκτέλεση του valgrind μέσα από τον φάκελο sigmod_run/final_testdriver