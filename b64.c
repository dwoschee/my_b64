/* b64.c */
#include <stdlib.h>

unsigned long b64_enc_req(unsigned long m_len) {
	/* Calculate number of bytes that need to be allocated for output */
	unsigned long n_triplets = m_len / 3;
	if (m_len % 3) {
		n_triplets++;
	}
	return n_triplets * 4;
}

unsigned char b64_enc_lut(unsigned char m) {
	/* Perform character lookup */
	unsigned char m64;
	if (m <= 25) {
		m64 = m + 65;
	} else if (m <= 51) {
		m64 = m + 71;
	} else if (m <= 61) {
		m64 = m - 4;
	} else if (m == 62) {
		m64 = '+';
	} else if (m == 63) {
		m64 = '/';
	} else {
		/* undefined value */
		m64 = '?';
	}
	return m64;
}

void b64_enc_full(const unsigned char m_in[3], unsigned char m_out[4]) {
	/* Base64-encode full byte triple */
	m_out[0] = b64_enc_lut(m_in[0]>>2);
	m_out[1] = b64_enc_lut((m_in[0]<<4 & 63) | m_in[1]>>4);
	m_out[2] = b64_enc_lut((m_in[1]<<2 & 63) | m_in[2]>>6);
	m_out[3] = b64_enc_lut(m_in[2] & 63);
}

void b64_enc_part(const unsigned char *m_in0, const unsigned char *m_in1, unsigned char m_out[4]) {
	/* Base64-encode non-full byte triple */
	m_out[0] = b64_enc_lut(*m_in0>>2);
	if (m_in1 != NULL) {
		m_out[1] = b64_enc_lut((*m_in0<<4 & 63) | *m_in1>>4);
		m_out[2] = b64_enc_lut(*m_in1<<2 & 63);
	} else {
		m_out[1] = b64_enc_lut(*m_in0<<4 & 63);
		m_out[2] = '=';
	}
	m_out[3] = '=';
}

void b64_encode(const unsigned char *msg_in, unsigned long msg_len, unsigned char *msg_out) {
	/* Write base64-encoded copy of `msg_in` with `msg_len` bytes to `msg_out` */
	unsigned long i;
	for (i = 0; i < msg_len/3; i++) {
		b64_enc_full(&msg_in[3*i], &msg_out[4*i]);
	}
	switch (msg_len % 3) {
		case 1:
			b64_enc_part(&msg_in[3*i], NULL, &msg_out[4*i]);
			break;

		case 2:
			b64_enc_part(&msg_in[3*i], &msg_in[3*i+1], &msg_out[4*i]);
			break;
	}
}
