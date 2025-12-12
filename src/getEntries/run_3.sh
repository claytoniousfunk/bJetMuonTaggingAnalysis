
#!/bin/bash

for i in {2001..3000}

do
    root -l -q "getEntries.C($i)"
done

