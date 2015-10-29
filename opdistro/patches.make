; opdistro make file for d.o. usage
core[] = "7.x"
api[] = "2"
projects[admin_theme][patch][] = patches/admin_theme/disable_admin_theme.patch
projects[backup_migrate][patch][] = patches/backup_migrate/backup_migrate-gzip-2494009.patch
projects[beautytips][patch][] = patches/beautytips/2038177_10_make-beautytips-features-exportable.patch
projects[beautytips][patch][] = patches/beautytips/beautytips-excanvas.patch
projects[beautytips][patch][] = patches/beautytips/beautytips-jquery-update-2059437-3.patch
projects[better_formats][patch][] = patches/better_formats/better_format-strict-warning-1717470-11.patch
projects[boxes][patch][] = patches/boxes/boxes-configure-link-2162465-3.patch
projects[bundle_copy][patch][] = patches/bundle_copy/bundle_copy-export_callback-2337607-2.patch
projects[content_taxonomy][patch][] = patches/content_taxonomy/content_taxonomy-migration-fails-1208164-16.patch
projects[context][patch][] = patches/context/context-inline_editor_needs_element_with_id_page-2283901-4-D7.patch
projects[context_og][patch][] = patches/context_og/context_og-member-role-not-saving-1988404-1.patch
projects[context_disable_context][patch][] = patches/context_disable_context/context_disable_context-unset-2052541-3.patch
projects[date][patch][] = patches/date/date-show_remaining_days_notice-2469189-1.patch
projects[devel][patch][] = patches/devel/1978250-devel-debug-mail-log.patch
projects[drupal][patch][] = patches/drupal/comment-hidden-2140251-4.patch
projects[drupal][patch][] = patches/drupal/contact-254460-7.x.patch
projects[drupal][patch][] = patches/drupal/error-user-notice-2309461-1.patch
projects[drupal][patch][] = patches/drupal/field_ui-multidefaults-1482386-61.patch
projects[drupal][patch][] = patches/drupal/mysql-fieldexists-escape-column-1885216-1.patch
projects[drupal][patch][] = patches/drupal/options-1585930-empty.patch
projects[drupal][patch][] = patches/drupal/watchdog.nofail.patch
projects[entityreference][patch][] = patches/entityreference/entityreference-1836106-20.patch
projects[entityreference][patch][] = patches/entityreference/entityreference-nonbase-relationships-2363287-1.patch
projects[entityreference_prepopulate][patch][] = patches/entityreference_prepopulate/entityreference_prepopulate-ajax-prepopulation-1958800-43-D7.patch
projects[features_override][patch][] = patches/features_override/features_override-identifier-dots-2475543.patch
projects[field_collection][patch][] = patches/field_collection/field-collection-2599248-2.patch
projects[logging_alerts][patch][] = patches/logging_alerts/logging_alerts-exclude-types-2435045-3.patch
projects[logintoboggan][patch][] = patches/logintoboggan/logintoboggan-1365764-conflicting-behaviours.patch
projects[mail_edit_features][patch][] = patches/mail_edit_features/mail_edit_features-feature_source-2165271-1.patch
projects[mail_logger][patch][] = patches/mail_logger/mail_logger-datetime-php52-2389521-1.patch
projects[node_export][patch][] = patches/node_export/node_export-combined-3.0.patch
projects[og][patch][] = patches/og/og-edit-group-audience-30.patch
projects[og][patch][] = patches/og/og-field_access_context_aware-1828514-7.patch
projects[og][patch][] = patches/og/og-gids-pathauto-tokens-2395659-for-2.7.patch
projects[og_vocab][patch][] = patches/og_vocab/og_vocab-unset-theme-2379169-1.patch
projects[rate][patch][] = patches/rate/rate-is_null_fix-1421016-9.patch
projects[rate][patch][] = patches/rate/rate-undefined_expiration_properties-2435219.patch
projects[reroute_email][patch][] = patches/reroute_email/reroute_email-whitelists-1571500-34.patch
projects[rules][patch][] = patches/rules/rules-install-fail-2449513-3.patch
projects[subscriptions][patch][] = patches/subscriptions/subscriptions-type-name-2023013-5-for1.1.patch
projects[subscriptions][patch][] = patches/subscriptions/subscriptions-fix_subscriptions_get-1853644-1.patch
projects[subscriptions][patch][] = patches/subscriptions/subscriptions-combined-2162519-2604466-for1.1.patch
projects[views_bulk_operations][patch][] = patches/views_bulk_operations/views_bulk_operations-warning-mb_strlen-2305227-3.patch
projects[views][patch][] = patches/views/1484208-views-undefined-index-help-topic-3.patch
projects[views][patch][] = patches/views/views-missing-comment-1816960-5.patch
projects[views][patch][] = patches/views/views-node_revision_count-959048-41.patch