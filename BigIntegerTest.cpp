#include"BigInteger.h"
#include"List.h"
int main() {
    printf("Commencing tests:\n");
    std::string s1=   "-39485700456000000000041085449";
    std::string s3 = "640277456935745645600000";
    BigInteger X = s1;
    BigInteger Y = s3;
    std::cout << "X: " << X << std::endl;
    std::cout << "Y: " << Y << std::endl;
    BigInteger K = Y + X;
    std::cout << "K: " << K << std::endl;
    BigInteger G = Y*X;
    std::cout << "G: " << G << std::endl;
    G = Y-X;
    std::cout << "G: " << G << std::endl;
    G -= X;
    std::cout << "G: " << G << std::endl;
    G += X;
    std::cout << "G: " << G << std::endl;
    G *= Y;
    std::cout << "G: " << G << std::endl;
    Y *= Y;
    G = Y-X;
    if (G == X) {
        printf("YOu dum fuked up");
        return 8;
    }
    std::cout << "Y: " << Y << std::endl;
    std::string s2 = "0";
    X = s2;
    Y = X*G;
    if (!(X==Y)) {
        printf("Sum ting wong masta");
        return 3;
    }
    std::cout << "Y: " << Y << std::endl;
    G *= G*X;
    std::cout << "G: " << G << std::endl;
    printf("Thus endeth the tests\n");
    return 0;
}
