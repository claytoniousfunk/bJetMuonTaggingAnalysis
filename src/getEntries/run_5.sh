
#!/bin/bash

for i in {4001..5000}

do
    root -l -q "getEntries.C($i)"
done

