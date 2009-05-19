/*
 *                         OpenSplice DDS
 *
 *   This software and documentation are Copyright 2006 to 2009 PrismTech 
 *   Limited and its licensees. All rights reserved. See file:
 *
 *                     $OSPL_HOME/LICENSE 
 *
 *   for full copyright notice and license terms. 
 *
 */
#ifndef U_PUBLISHER_H
#define U_PUBLISHER_H

/** \file u_publisher.h
 * \brief The publisher class is responsible for data distribution.
 *
 * The data can be written to a publisher via associated typed u_writer objects.
 * A publisher will distribute the data to all domains associated to the publisher.
 * The publisher also offers methods to control the distribution of data.
 * The distribution can be suspended or performed in a coherent manner.
 *
 * This class specifies object that implement a proxy to kernel publishers
 * and offers methods implementing the functionality as described above.
 */

/** Supported methods
 * u_publisher u_publisherNew           (u_participant p,
 *                                       const c_char *name,
 *                                       v_publisherQos qos);
 * u_result    u_publisherFree          (u_publisher p);
 * u_result    u_publisherPublish       (u_publisher p,
 *                                       const c_char *domainExpr);
 * u_result    u_publisherUnPublish     (u_publisher p,
 *                                       const c_char *domainExpr);
 * u_result    u_publisherSuspend       (u_publisher p);
 * u_result    u_publisherResume        (u_publisher p);
 * u_result    u_publisherCoherentBegin (u_publisher p);
 * u_result    u_publisherCoherentEnd   (u_publisher p);
*/

#if defined (__cplusplus)
extern "C" {
#endif

#include "u_types.h"
#include "os_if.h"

#ifdef OSPL_BUILD_USER
#define OS_API OS_API_EXPORT
#else
#define OS_API OS_API_IMPORT
#endif
/* !!!!!!!!NOTE From here no more includes are allowed!!!!!!! */

/** \brief The u_publisher cast method.
 *
 * In comparison with kernel classes this cast method will not perform
 * runtime type checking due to the lack of type information.
 */
#define u_publisher(p) ((u_publisher)(p))

/** \brief The class constructor.
 *
 * The constructor will create a kernel publisher and publisher proxy within
 * the scope of the specified participant.
 *
 * \param _this the participant that must be specified.
 * \param name an optional name that can be used to identify a publisher.
 * \param qos an optional parameter to specify publisher specific quality of
 *        service settings.
 * \return the created publisher proxy on a succesful operation or NULL
 *         if the operation failed.
 */
OS_API u_publisher
u_publisherNew (
    u_participant _this,
    const c_char *name,
    v_publisherQos qos,
    c_bool enable);

/** \brief The class destructor.
 *
 * The destructor notifies the kernel to destruct the kernel publisher
 * associated to this proxy. Also all kernel object owned by the deleted kernel
 * publisher are deleted.
 *
 * \param _this The publisher to operate on.
 * \return U_RESULT_OK on a succesful operation or
 *         U_RESULT_ILL_PARAM if the specified participant is incorrect.
 */
OS_API u_result
u_publisherFree (
    u_publisher _this);

/** \brief Specifies an additional data distribution scope.
 *
 * Data is always distributed in domain (dds: partitions).
 * This method specifies via a domain expression which currently
 * known domains must be added to the publishers distribution scope.
 *
 * \param _this The publisher to operate on.
 * \param domainExpr The expression specifying the namespace of the domains that
 *        must be added to the publishers distribution scope. The expression
 *        specifies the domain name and may contain wildcards * and ?.
 * \return U_RESULT_OK on a succesful operation.
 */
OS_API u_result
u_publisherPublish (
    u_publisher _this,
    const c_char *domainExpr);

/** \brief Specifies a substractable data distribution scope.
 *
 * Data is always distributed in domain (dds: partitions).
 * This method specifies via a domain expression which currently
 * known domains must be removed from the publishers distribution scope.
 *
 * \param _this The publisher to operate on.
 * \param domainExpr The expression specifying the namespace of the domains that
 *        must be removed from the publishers distribution scope. The expression
 *        specifies the domain name and may contain wildcards * and ?.
 * \return U_RESULT_OK on a succesful operation.
 */
OS_API u_result
u_publisherUnPublish (
    u_publisher _this,
    const c_char *domainExpr);

/** \brief Suspend data distribution until resume is called.
 *
 * This method will stop data distribution but processes can still write
 * data via the data writers until the publisher internal buffer has no
 * more space left to store messages.
 * Then the QoS setting determine whether writing data will block or
 * that old data will be overwritten.
 *
 * \param _this The publisher this method will operate on.
 * \return U_RESULT_OK
 */
OS_API u_result
u_publisherSuspend (
    u_publisher _this);

/** \brief The resume method: resumes previously suspended data distribution.
 *
 * This method will resume data distribution.
 *
 * \param _this The publisher this method will operate on.
 * \return U_RESULT_OK
 */
OS_API u_result
u_publisherResume (
    u_publisher _this);

/** \brief Set the beginning of a coherent set of data to be distributed.
 *
 * This method is used in combination with u_publisherCoherentEnd,
 * both specifying the beginning and the end of a coherent set of data
 * to be distributed.
 * Data written between these calls are written in a coherent manner
 * according to the coherency scope that is specified by the publishers QoS.
 *
 * \param _this The publisher this method will operate on.
 * \return U_RESULT_OK
 */
OS_API u_result
u_publisherCoherentBegin (
    u_publisher _this);

/** \brief Set the end of a coherent set of data to be distributed.
 *
 * This method is used in combination with u_publisherCoherentBegin,
 * both specifying the beginning and the end of a coherent set of data
 * to be distributed.
 * Data written between these calls are written in a coherent manner
 * according to the coherency scope that is specified by the publishers QoS.
 *
 * \param _this The publisher this method will operate on.
 * \return U_RESULT_OK
 */
OS_API u_result
u_publisherCoherentEnd (
    u_publisher _this);

#undef OS_API 

#if defined (__cplusplus)
}
#endif

#endif