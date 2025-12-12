
#!/bin/bash

for i in {6001..6240}

do
    root -l -q "getEntries.C($i)"
done

