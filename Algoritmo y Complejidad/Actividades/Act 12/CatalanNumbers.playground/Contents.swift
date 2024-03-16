import Foundation

func catalan(number n: Int) -> Int {
    var c = 0
    
    if( n==0 || n==1 ){
        c = 1
    } else {
        for i in 0...n-1 {
            c = c + catalan(number: i) * catalan(number: n-i-1)
        }
    }
    return c
}

print("Catalan de 0: \(catalan(number: 0))")
print("Catalan de 1: \(catalan(number: 1))")
print("Catalan de 2: \(catalan(number: 2))")
print("Catalan de 3: \(catalan(number: 3))")
print("Catalan de 4: \(catalan(number: 4))")
print("Catalan de 5: \(catalan(number: 5))")
print("Catalan de 6: \(catalan(number: 6))")
print("Catalan de 7: \(catalan(number: 7))")

