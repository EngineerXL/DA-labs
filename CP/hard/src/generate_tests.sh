cd tests
for (( t = 1; t <= 99; t++ ));
do
	rm -rf "$t.nodes" "$t.edges" "$t.in" "$t.out"
	touch "$t.nodes" "$t.edges" "$t.in" "$t.out"
done
