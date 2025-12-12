
#!/bin/bash

for i in {5001..6000}

do
    root -l -q "getEntries.C($i)"
done

