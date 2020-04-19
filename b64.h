/* b64.h */

unsigned long b64_enc_req(unsigned long m_len);

void b64_encode(const unsigned char *msg_in, unsigned long msg_len, unsigned char *msg_out);
