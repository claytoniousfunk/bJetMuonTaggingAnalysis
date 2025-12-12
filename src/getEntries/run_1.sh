
#!/bin/bash

for i in {1..1000}

do
    root -l -q "getEntries.C($i)"
done

