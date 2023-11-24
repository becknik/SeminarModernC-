let fibGeneratorInstance = function* fibGenerator() {
	let a = 0; let b = 1;
	yield a; yield b;
	while ( b != 'Infinity' ) {
		const tmp = b;
		b = a + b;
		a = tmp;
		yield b;
	}
}();
for ( const fib of fibGeneratorInstance ) {
	console.log( fib );
}