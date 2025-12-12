
#!/bin/bash

for i in {1..6300}

do
    root -l -q "getEntries.C($i)"
done

