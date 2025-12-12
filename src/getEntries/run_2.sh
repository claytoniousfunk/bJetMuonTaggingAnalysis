
#!/bin/bash

for i in {1001..2000}

do
    root -l -q "getEntries.C($i)"
done

