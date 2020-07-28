#include <assert.h>
#include <string.h>
#include <tirpc/rpc/des_crypt.h>

#define PASS_MAX_LEN (14)
#define FRAGMENT_LEN (PASS_MAX_LEN / 2)
#define FRAGMENT_OFFSET (FRAGMENT_LEN)

void frag_and_padding();
void DES_CRYPT();

int main(int argc, char **argv)
{
    char pass[PASS_MAX_LEN + 1];
    uint8_t count;
    char frag[17];
    uint8_t frag1[8];
    uint8_t frag2[8];
    uint8_t frag1_new[9];
    uint8_t frag2_new[9];

    // max len limits
    assert(strlen(argv[1]) <= PASS_MAX_LEN);

    // store pass
    memset(pass, 0x00, sizeof(pass));
    strncpy(pass, argv[1], strlen(argv[1]));

    // upper pass
    for (count = 0; count < strlen(pass); count ++) {
        if (pass[count] >= 'a' && pass[count] <= 'z')
            pass[count] -= 0x20;
    }

    //printf("%s\n", pass);

    // two 7byte fragments
    memset(frag, 0x00, sizeof(frag));
    //strncpy(frag1, pass, FRAGMENT_LEN);
    //strncpy(frag2, pass + FRAGMENT_OFFSET, FRAGMENT_LEN);
    memcpy(frag1, pass, FRAGMENT_LEN);
    memcpy(frag2, pass + FRAGMENT_OFFSET, FRAGMENT_LEN);

    memset(frag1_new, 0x00, sizeof(frag1_new));
    memset(frag2_new, 0x00, sizeof(frag2_new));

    uint8_t mask = ~(0x01);
    uint8_t r = 0;
    uint8_t n = 0;

    for (count = 0; count < FRAGMENT_LEN; count ++) {
        //printf("%d %x %x %d\n", count, pass[count], r << (8-count), r);
        frag1_new[count] = (((frag1[count] & mask) >> count >> 1) + (r << (count ^ 0x07))) << 1;
        r = frag1[count] & (~mask);
        mask <<= 1;
        if (count == 6) {
            frag1_new[count + 1] = r << 1;
        }
        printf("%x\n", frag1_new[count]);
    }

    printf("%x\n", frag1_new[count]);
    mask = ~(0x01);
    r = 0;
    n = 0;
    for (count = 0; count < FRAGMENT_LEN; count ++) {
        //printf("%d %x %x %d\n", count, pass[count], r << (8-count), r);
        frag2_new[count] = (((frag2[count] & mask) >> count >> 1) + (r << (count ^ 0x07))) << 1;
        r = frag2[count] & (~mask);
        mask <<= 1;
        if (count == 6) {
            frag2_new[count + 1] = r << 1;
        }
        printf("%x\n", frag2_new[count]);
    }

    printf("%x\n", frag2_new[count]);
    //DES_CRYPT();
    
    char block1[9];
    char block2[9];

    memset(block1, 0x00, sizeof(block1));
    memset(block2, 0x00, sizeof(block2));

    memcpy(block1, frag1_new, sizeof(frag1_new));
    memcpy(block2, frag2_new, sizeof(frag2_new));

    ecb_crypt("KGS!@#$%", block1, strlen(block1), DES_ENCRYPT);
    ecb_crypt("KGS!@#$%", block2, strlen(block2), DES_ENCRYPT);

    for (count = 0; count < 8; count ++) {
        printf("%#x\n", block1[count]);
    }
    for (count = 0; count < 8; count ++) {
        printf("%#x\n", block2[count]);
    }

    return 0;
}
