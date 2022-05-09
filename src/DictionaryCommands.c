/********************************************************************************/
/*										*/
/*			  Dictionary Attack Functions  				*/
/*			     Written by Ken Goldman				*/
/*		       IBM Thomas J. Watson Research Center			*/
/*            $Id: DictionaryCommands.c 1490 2019-07-26 21:13:22Z kgoldman $	*/
/*										*/
/*  Licenses and Notices							*/
/*										*/
/*  1. Copyright Licenses:							*/
/*										*/
/*  - Trusted Computing Group (TCG) grants to the user of the source code in	*/
/*    this specification (the "Source Code") a worldwide, irrevocable, 		*/
/*    nonexclusive, royalty free, copyright license to reproduce, create 	*/
/*    derivative works, distribute, display and perform the Source Code and	*/
/*    derivative works thereof, and to grant others the rights granted herein.	*/
/*										*/
/*  - The TCG grants to the user of the other parts of the specification 	*/
/*    (other than the Source Code) the rights to reproduce, distribute, 	*/
/*    display, and perform the specification solely for the purpose of 		*/
/*    developing products based on such documents.				*/
/*										*/
/*  2. Source Code Distribution Conditions:					*/
/*										*/
/*  - Redistributions of Source Code must retain the above copyright licenses, 	*/
/*    this list of conditions and the following disclaimers.			*/
/*										*/
/*  - Redistributions in binary form must reproduce the above copyright 	*/
/*    licenses, this list of conditions	and the following disclaimers in the 	*/
/*    documentation and/or other materials provided with the distribution.	*/
/*										*/
/*  3. Disclaimers:								*/
/*										*/
/*  - THE COPYRIGHT LICENSES SET FORTH ABOVE DO NOT REPRESENT ANY FORM OF	*/
/*  LICENSE OR WAIVER, EXPRESS OR IMPLIED, BY ESTOPPEL OR OTHERWISE, WITH	*/
/*  RESPECT TO PATENT RIGHTS HELD BY TCG MEMBERS (OR OTHER THIRD PARTIES)	*/
/*  THAT MAY BE NECESSARY TO IMPLEMENT THIS SPECIFICATION OR OTHERWISE.		*/
/*  Contact TCG Administration (admin@trustedcomputinggroup.org) for 		*/
/*  information on specification licensing rights available through TCG 	*/
/*  membership agreements.							*/
/*										*/
/*  - THIS SPECIFICATION IS PROVIDED "AS IS" WITH NO EXPRESS OR IMPLIED 	*/
/*    WARRANTIES WHATSOEVER, INCLUDING ANY WARRANTY OF MERCHANTABILITY OR 	*/
/*    FITNESS FOR A PARTICULAR PURPOSE, ACCURACY, COMPLETENESS, OR 		*/
/*    NONINFRINGEMENT OF INTELLECTUAL PROPERTY RIGHTS, OR ANY WARRANTY 		*/
/*    OTHERWISE ARISING OUT OF ANY PROPOSAL, SPECIFICATION OR SAMPLE.		*/
/*										*/
/*  - Without limitation, TCG and its members and licensors disclaim all 	*/
/*    liability, including liability for infringement of any proprietary 	*/
/*    rights, relating to use of information in this specification and to the	*/
/*    implementation of this specification, and TCG disclaims all liability for	*/
/*    cost of procurement of substitute goods or services, lost profits, loss 	*/
/*    of use, loss of data or any incidental, consequential, direct, indirect, 	*/
/*    or special damages, whether under contract, tort, warranty or otherwise, 	*/
/*    arising in any way out of use or reliance upon this specification or any 	*/
/*    information herein.							*/
/*										*/
/*  (c) Copyright IBM Corp. and others, 2016 - 2021				*/
/*										*/
/********************************************************************************/

#include "Tpm.h"
#include "DictionaryAttackLockReset_fp.h"

extern int verbose;

#if CC_DictionaryAttackLockReset  // Conditional expansion of this file
TPM_RC
TPM2_DictionaryAttackLockReset(
			       DictionaryAttackLockReset_In    *in             // IN: input parameter list
			       )
{
    if (verbose) {
	FILE *f = fopen("trace.txt", "a");
	fprintf(f, "TPM2_DictionaryAttackLockReset: lockHandle %08x\n", in->lockHandle);
	fclose(f);
    }
    // Input parameter is not reference in command action
    NOT_REFERENCED(in);
    // The command needs NV update.
    RETURN_IF_NV_IS_NOT_AVAILABLE;
    // Internal Data Update
    // Set failed tries to 0
    gp.failedTries = 0;
    // Record the changes to NV
    NV_SYNC_PERSISTENT(failedTries);
    return TPM_RC_SUCCESS;
}
#endif // CC_DictionaryAttackLockReset
#include "Tpm.h"
#include "DictionaryAttackParameters_fp.h"
#if CC_DictionaryAttackParameters  // Conditional expansion of this file
TPM_RC
TPM2_DictionaryAttackParameters(
				DictionaryAttackParameters_In   *in             // IN: input parameter list
				)
{
    if (verbose) {
	FILE *f = fopen("trace.txt", "a");
	fprintf(f, "TPM2_DictionaryAttackParameters: lockHandle %08x\n", in->lockHandle);
	fclose(f);
    }
    // The command needs NV update.
    RETURN_IF_NV_IS_NOT_AVAILABLE;
    // Internal Data Update
    // Set dictionary attack parameters
    gp.maxTries = in->newMaxTries;
    gp.recoveryTime = in->newRecoveryTime;
    gp.lockoutRecovery = in->lockoutRecovery;
    // Record the changes to NV
    NV_SYNC_PERSISTENT(failedTries);
    NV_SYNC_PERSISTENT(maxTries);
    NV_SYNC_PERSISTENT(recoveryTime);
    NV_SYNC_PERSISTENT(lockoutRecovery);
    return TPM_RC_SUCCESS;
}
#endif // CC_DictionaryAttackParameters
